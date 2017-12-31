
cmake_minimum_required(VERSION 3.4.1)

INCLUDE_DIRECTORIES(
    src/melt
    src/framework
    src/mlt++
    src/modules/core
    src/modules/avformat
    src/
)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(AVCODEC REQUIRED libavcodec)
pkg_search_module(AVFORMAT REQUIRED libavformat)
pkg_search_module(AVUTIL REQUIRED libavutil)
pkg_search_module(AVRESAMPLE REQUIRED libavresample)
pkg_search_module(AVDEVICE REQUIRED libavdevice)
pkg_search_module(AVFILTER REQUIRED libavfilter)
pkg_search_module(SWSCALE REQUIRED libswscale)

set(FRAMEWORK_SRC_FILES
    src/framework/mlt_frame.c
    src/framework/mlt_version.c
    src/framework/mlt_geometry.c
    src/framework/mlt_deque.c
    src/framework/mlt_property.c
    src/framework/mlt_properties.c
    src/framework/mlt_events.c
    src/framework/mlt_parser.c
    src/framework/mlt_service.c
    src/framework/mlt_producer.c
    src/framework/mlt_multitrack.c
    src/framework/mlt_playlist.c
    src/framework/mlt_consumer.c
    src/framework/mlt_filter.c
    src/framework/mlt_transition.c
    src/framework/mlt_field.c
    src/framework/mlt_tractor.c
    src/framework/mlt_factory.c
    src/framework/mlt_repository.c
    src/framework/mlt_pool.c
    src/framework/mlt_tokeniser.c
    src/framework/mlt_profile.c
    src/framework/mlt_log.c
    src/framework/mlt_cache.c
    src/framework/mlt_animation.c
    src/framework/mlt_slices.c
)

set(MLTCPP_SRC_FILES
    src/mlt++/MltAnimation.cpp
    src/mlt++/MltConsumer.cpp
    src/mlt++/MltDeque.cpp
    src/mlt++/MltEvent.cpp
    src/mlt++/MltFactory.cpp
    src/mlt++/MltField.cpp
    src/mlt++/MltFilter.cpp
    src/mlt++/MltFilteredConsumer.cpp
    src/mlt++/MltFilteredProducer.cpp
    src/mlt++/MltFrame.cpp
    src/mlt++/MltGeometry.cpp
    src/mlt++/MltMultitrack.cpp
    src/mlt++/MltParser.cpp
    src/mlt++/MltPlaylist.cpp
    src/mlt++/MltProducer.cpp
    src/mlt++/MltProfile.cpp
    src/mlt++/MltProperties.cpp
    src/mlt++/MltPushConsumer.cpp
    src/mlt++/MltRepository.cpp
    src/mlt++/MltService.cpp
    src/mlt++/MltTokeniser.cpp
    src/mlt++/MltTractor.cpp
    src/mlt++/MltTransition.cpp
)

set(CORE_SRC_FILES
    ./src/modules/core//producer_tone.c
    ./src/modules/core//filter_brightness.c
    ./src/modules/core//filter_panner.c
    ./src/modules/core//filter_data_show.c
    ./src/modules/core//filter_greyscale.c
    ./src/modules/core//transition_composite.c
    ./src/modules/core//filter_mirror.c
    ./src/modules/core//filter_audioconvert.c
    ./src/modules/core//filter_mono.c
    ./src/modules/core//filter_luma.c
    ./src/modules/core//composite_line_yuv_sse2_simple.c
    ./src/modules/core//filter_audiochannels.c
    ./src/modules/core//transition_matte.c
    ./src/modules/core//consumer_null.c
    ./src/modules/core//filter_gamma.c
    ./src/modules/core//filter_crop.c
    ./src/modules/core//filter_data_feed.c
    ./src/modules/core//producer_loader.c
    ./src/modules/core//filter_watermark.c
    ./src/modules/core//factory.c
    ./src/modules/core//producer_noise.c
    ./src/modules/core//filter_fieldorder.c
    ./src/modules/core//transition_luma.c
    ./src/modules/core//filter_channelcopy.c
    ./src/modules/core//producer_melt.c
    ./src/modules/core//transition_region.c
    ./src/modules/core//producer_timewarp.c
    ./src/modules/core//transition_mix.c
    ./src/modules/core//filter_imageconvert.c
    ./src/modules/core//filter_audiowave.c
    ./src/modules/core//producer_consumer.c
    ./src/modules/core//filter_obscure.c
    ./src/modules/core//producer_colour.c
    ./src/modules/core//consumer_multi.c
    ./src/modules/core//filter_resize.c
    ./src/modules/core//filter_rescale.c
    ./src/modules/core//producer_hold.c
    ./src/modules/core//filter_audiomap.c
    ./src/modules/core//filter_transition.c
    ./src/modules/core//filter_region.c
)

set(AVFORMAT_SRC_FILES
    src/modules/avformat//consumer_avformat.c
    src/modules/avformat//filter_avfilter.c
    src/modules/avformat//producer_avformat.c
    src/modules/avformat//filter_avcolour_space.c
    src/modules/avformat//factory.c
    src/modules/avformat//filter_avdeinterlace.c
#src/modules/avformat//vdpau.c
    src/modules/avformat//filter_swscale.c
)

set(SDL_SRC_FILES
    src/modules/sdl//factory.c
    src/modules/sdl//consumer_sdl_audio.c
    src/modules/sdl//consumer_sdl2.c
    src/modules/sdl//consumer_sdl_osx.m
)

set(MELT_SRC_FILES
    src/melt/melt.c
    src/melt/io.c
)

add_library( mlt SHARED ${FRAMEWORK_SRC_FILES} )

set_target_properties(mlt PROPERTIES COMPILE_FLAGS

    "-DARCH_X86_64 -Wall -DPIC -DUSE_MMX -DUSE_SSE -DUSE_SSE2 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fPIC  -DPREFIX_DATA=\"\\\"/usr/local/share/mlt\\\"\" -DPREFIX_LIB=\"\\\"/usr/local/lib/mlt\\\"\"   -c"
)

add_library( mlt++ SHARED ${MLTCPP_SRC_FILES} )

set_target_properties(mlt++ PROPERTIES COMPILE_FLAGS

    "-Wall -DPIC -DUSE_MMX -DUSE_SSE -DUSE_SSE2 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -Wall -fPIC -I..  -DVERSION=\\\"6.5.0\\\" -fvisibility=hidden   -c"
)

target_link_libraries(mlt++

        mlt
)

add_library( core SHARED ${CORE_SRC_FILES} )

set_target_properties(core PROPERTIES COMPILE_FLAGS

    "-DARCH_X86_64 -Wall -DPIC -DUSE_MMX -DUSE_SSE -DUSE_SSE2 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fPIC   -c"
)

target_link_libraries(core

    mlt
)

add_library( mltavformat SHARED ${AVFORMAT_SRC_FILES} )

set_target_properties(mltavformat PROPERTIES COMPILE_FLAGS

    "-DARCH_X86_64 -Wall -DPIC -DUSE_MMX -DUSE_SSE -DUSE_SSE2 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fPIC -DAVDATADIR=\\\"/usr/local/Cellar/ffmpeg/3.4.1/share/ffmpeg/\\\" -I/usr/local/Cellar/ffmpeg/3.4.1/include -I/usr/local/Cellar/ffmpeg/3.4.1/include -I/usr/local/Cellar/ffmpeg/3.4.1/include -I/usr/local/Cellar/ffmpeg/3.4.1/include -I/usr/local/Cellar/ffmpeg/3.4.1/include -I/usr/local/Cellar/ffmpeg/3.4.1/include -DFILTERS -DCODECS -DAVDEVICE -DAVFILTER   -c"
)

target_include_directories( mltavformat

    PUBLIC

    ${AVCODEC_INCLUDE_DIRS}
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    ${AVRESAMPLE_INCLUDE_DIRS}
    ${AVDEVICE_INCLUDE_DIRS}
    ${AVFILTER_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
)

target_link_libraries(mltavformat

    mlt
    ${AVCODEC_LDFLAGS}
    ${AVFORMAT_LDFLAGS}
    ${AVUTIL_LDFLAGS}
    ${AVRESAMPLE_LDFLAGS}
    ${AVDEVICE_LDFLAGS}
    ${AVFILTER_LDFLAGS}
    ${SWSCALE_LDFLAGS}
)

add_library( mltsdl SHARED ${SDL_SRC_FILES} )

set_target_properties(mltsdl PROPERTIES COMPILE_FLAGS

    "-DARCH_X86_64 -Wall -DPIC -DUSE_MMX -DUSE_SSE -DUSE_SSE2 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fPIC -ObjC -D_THREAD_SAFE -I/usr/local/include/SDL2   -c"
)

target_include_directories( mltsdl

    PUBLIC

    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(mltsdl

    mlt
    ${SDL2_LDFLAGS}
)

add_executable(melt ${MELT_SRC_FILES} )

target_include_directories( melt

            PUBLIC

            ${SDL2_INCLUDE_DIRS}
)

target_link_libraries( melt

            mlt
            mlt++
            core
            mltavformat
            mltsdl
            ${SDL2_LDFLAGS}
            )

