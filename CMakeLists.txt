
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "-x objective-c++ -std=c++11")

INCLUDE_DIRECTORIES(
    src/ZPlayer
)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(XML2 REQUIRED libxml-2.0)
pkg_search_module(AVCODEC REQUIRED libavcodec)
pkg_search_module(AVFORMAT REQUIRED libavformat)
pkg_search_module(AVUTIL REQUIRED libavutil)
pkg_search_module(AVRESAMPLE REQUIRED libavresample)
pkg_search_module(AVDEVICE REQUIRED libavdevice)
pkg_search_module(AVFILTER REQUIRED libavfilter)
pkg_search_module(SWSCALE REQUIRED libswscale)
pkg_search_module(SWRESAMPLE REQUIRED libswresample)

add_executable(ZPlayer src/ZPlayer/ZPlayer.cpp)

target_include_directories( ZPlayer

    PUBLIC

    ${AVCODEC_INCLUDE_DIRS}
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    ${AVRESAMPLE_INCLUDE_DIRS}
    ${AVDEVICE_INCLUDE_DIRS}
    ${AVFILTER_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries( ZPlayer

    ${SDL2_LDFLAGS}
    ${AVCODEC_LDFLAGS}
    ${AVFORMAT_LDFLAGS}
    ${AVUTIL_LDFLAGS}
    ${AVRESAMPLE_LDFLAGS}
    ${AVDEVICE_LDFLAGS}
    ${AVFILTER_LDFLAGS}
    ${SWSCALE_LDFLAGS}
    ${SWRESAMPLE_LDFLAGS}
)
