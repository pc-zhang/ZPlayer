
cmake_minimum_required(VERSION 3.4.1)

add_definitions(-DCODECS -DFILTERS)

INCLUDE_DIRECTORIES(
    src/melt
    src/framework
    src/mlt++
    src/modules/core
    src/modules/avformat
    src/
)

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
    src/mlt++/mlt_wrap.cxx
)

set(CORE_SRC_FILES
    src/core/factory.c
    src/core/producer_colour.c
    src/core/producer_consumer.c
    src/core/producer_hold.c
    src/core/producer_loader.c
    src/core/producer_melt.c
    src/core/producer_noise.c
    src/core/producer_timewarp.c
    src/core/producer_tone.c
    src/core/filter_audiochannels.c
    src/core/filter_audiomap.c
    src/core/filter_audioconvert.c
    src/core/filter_audiowave.c
    src/core/filter_brightness.c
    src/core/filter_channelcopy.c
    src/core/filter_crop.c
    src/core/filter_data_feed.c
    src/core/filter_data_show.c
    src/core/filter_fieldorder.c
    src/core/filter_gamma.c
    src/core/filter_greyscale.c
    src/core/filter_imageconvert.c
    src/core/filter_luma.c
    src/core/filter_mirror.c
    src/core/filter_mono.c
    src/core/filter_obscure.c
    src/core/filter_panner.c
    src/core/filter_region.c
    src/core/filter_rescale.c
    src/core/filter_resize.c
    src/core/filter_transition.c
    src/core/filter_watermark.c
    src/core/transition_composite.c
    src/core/transition_luma.c
    src/core/transition_mix.c
    src/core/transition_region.c
    src/core/transition_matte.c
    src/core/consumer_multi.c
    src/core/consumer_null.c
)

set(AVFORMAT_SRC_FILES
    src/producer_avformat/consumer_avformat.c
    src/producer_avformat/filter_avfilter.c
    src/producer_avformat/producer_avformat.c
    src/producer_avformat/filter_avcolour_space.c
    src/producer_avformat/factory.c
    src/producer_avformat/filter_avdeinterlace.c
    #src/producer_avformat/vdpau.c
    src/producer_avformat/filter_swscale.c
)

set(MELT_SRC_FILES
    src/melt/melt.c
    src/melt/io.c
)

add_executable(melt ${MELT_SRC_FILES} )

#add_library( ttvideoeditor SHARED ${TE_WRAPPER_SRC_FILES} )

find_library( mlt-lib mlt )
find_library( SDL2-lib SDL2 )

target_include_directories( melt

            PUBLIC

            /usr/local/include/mlt
            /usr/local/include/SDL2
)

target_link_libraries( melt

            ${mlt-lib}
            ${SDL2-lib}
            )

