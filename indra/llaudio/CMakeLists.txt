# -*- cmake -*-

project(llaudio)

include(00-Common)
include(LLAudio)
include(FMODSTUDIO)
include(OPENAL)
include(LLCommon)

set(llaudio_SOURCE_FILES
    llaudioengine.cpp
    lllistener.cpp
    llaudiodecodemgr.cpp
    llvorbisencode.cpp
    )

set(llaudio_HEADER_FILES
    CMakeLists.txt

    llaudioengine.h
    lllistener.h
    llaudiodecodemgr.h
    llstreamingaudio.h
    llvorbisencode.h
    llwindgen.h
    )

if (TARGET ll::fmodstudio)
    list(APPEND llaudio_SOURCE_FILES
         llaudioengine_fmodstudio.cpp
         lllistener_fmodstudio.cpp
         llstreamingaudio_fmodstudio.cpp
         )

    list(APPEND llaudio_HEADER_FILES
         llaudioengine_fmodstudio.h
         lllistener_fmodstudio.h
         llstreamingaudio_fmodstudio.h
         )
endif ()

if (TARGET ll::openal)
  list(APPEND llaudio_SOURCE_FILES
    llaudioengine_openal.cpp
    lllistener_openal.cpp
    )
  
  list(APPEND llaudio_HEADER_FILES
    llaudioengine_openal.h
    lllistener_openal.h
    )
endif ()

list(APPEND llaudio_SOURCE_FILES ${llaudio_HEADER_FILES})

add_library (llaudio ${llaudio_SOURCE_FILES})
target_include_directories( llaudio  INTERFACE   ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries( llaudio
        PUBLIC
        llcommon
        llmath
        llmessage
        llfilesystem
        ll::vorbis
    )

if( TARGET ll::openal )
    target_link_libraries( llaudio PUBLIC ll::openal )
endif()
if( TARGET ll::fmodstudio )
    target_link_libraries( llaudio PUBLIC ll::fmodstudio )
endif()

if(USE_PRECOMPILED_HEADERS AND ${CMAKE_VERSION} VERSION_GREATER "3.15.0") 
  target_precompile_headers(llaudio
    PRIVATE
    [["linden_common.h"]]
    )
endif()


