extern "C" {
#include "libavformat/avformat.h"
    
#include <SDL.h>
#include <SDL_thread.h>
}

#include <assert.h>
#include <mutex>
#include <condition_variable>

static const char *input_filename = "https://aweme.snssdk.com/aweme/v1/playwm/?video_id=54a1da191aa940459e4c21e919e62309&line=0";

#define SDL_AUDIO_BUFFER_SIZE 1024

static uint8_t audio_buf[44100*16*2*4];
static unsigned int audio_buf_left_index = 0;
static unsigned int audio_buf_right_index = 0;
static std::condition_variable m_enoughSamplesCondition;
static std::mutex m_mutex;

void audio_callback(void *userdata, Uint8 *stream, int len) {
    std::unique_lock<std::mutex> lk(m_mutex);
    m_enoughSamplesCondition.wait(lk, [len] { return len <= audio_buf_right_index - audio_buf_left_index; });
    memcpy(stream, audio_buf + audio_buf_left_index, len);
    audio_buf_left_index += len;
}

/* Called from the main */
int main(int argc, char **argv)
{
    av_register_all();
    avformat_network_init();
    
    AVFormatContext *pFormatContext = avformat_alloc_context();
    avformat_open_input(&pFormatContext, input_filename, nullptr, nullptr);
    avformat_find_stream_info(pFormatContext, nullptr);
    av_dump_format(pFormatContext, 0, input_filename, 0);
    
    int video_stream_index = av_find_best_stream(pFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    AVCodecContext *pVideoCodecCtx = pFormatContext->streams[video_stream_index]->codec;
    AVCodec *pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
    assert(avcodec_open2(pVideoCodecCtx, pVideoCodec, nullptr) >= 0);
    
    int audio_stream_index = av_find_best_stream(pFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    AVCodecContext *pAudioCodecCtx = pFormatContext->streams[audio_stream_index]->codec;
    AVCodec *pAudioCodec = avcodec_find_decoder(pAudioCodecCtx->codec_id);
    assert(avcodec_open2(pAudioCodecCtx, pAudioCodec, nullptr) >= 0);
    
    assert(0==SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER));
    SDL_Window * window = SDL_CreateWindow("ZPlayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pVideoCodecCtx->width, pVideoCodecCtx->height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = pVideoCodecCtx->width;
    rect.h = pVideoCodecCtx->height;
    
    SDL_AudioSpec desired_spec;
    SDL_AudioSpec obtained_spec;
    desired_spec.freq = pAudioCodecCtx->sample_rate;
    desired_spec.format = AUDIO_F32SYS;
    desired_spec.channels = pAudioCodecCtx->channels;
    desired_spec.silence = 0;
    desired_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    desired_spec.callback = audio_callback;
    desired_spec.userdata = audio_buf;
    
    assert(SDL_OpenAudio(&desired_spec, &obtained_spec) >= 0);
    SDL_PauseAudio(0);
    
    
    AVPacket pkt;
    while(av_read_frame(pFormatContext, &pkt)>=0){
        if(pkt.stream_index == video_stream_index){
            
            avcodec_send_packet(pVideoCodecCtx, &pkt);
            
            AVFrame *picture = av_frame_alloc();
            if(avcodec_receive_frame(pVideoCodecCtx, picture) >= 0){
                SDL_Texture *vid_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, picture->width, picture->height);
                
                SDL_UpdateYUVTexture(vid_texture, NULL,
                                     picture->data[0], picture->linesize[0],
                                     picture->data[1], picture->linesize[1],
                                     picture->data[2], picture->linesize[2]);
                
                SDL_RenderCopyEx(renderer, vid_texture, NULL, &rect, 0, NULL, (SDL_RendererFlip)0);
                SDL_RenderPresent(renderer);
            }
        } else if(pkt.stream_index == audio_stream_index) {
            avcodec_send_packet(pAudioCodecCtx, &pkt);
            
            AVFrame *frame = av_frame_alloc();
            if(avcodec_receive_frame(pAudioCodecCtx, frame) >= 0) {
                std::unique_lock<std::mutex> lk(m_mutex);
                int uSampleSize = 4;
                
                int data_size = uSampleSize * pAudioCodecCtx->channels * frame->nb_samples;
                
                uint8_t *pBufferIterator = audio_buf + audio_buf_right_index;
                for(int i=0;i<frame->nb_samples;i++){
                    for(int j=0;j<pAudioCodecCtx->channels;j++){
                        memcpy(pBufferIterator, frame->data[j] + uSampleSize * i, uSampleSize);
                        pBufferIterator += uSampleSize;
                    }
                }
                
                audio_buf_right_index += data_size;
                m_enoughSamplesCondition.notify_one();
            }
        }
    }
    
    return 0;
}
