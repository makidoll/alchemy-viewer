# -*- cmake -*-

project(llcharacter)

include(00-Common)
include(LLCommon)

set(llcharacter_SOURCE_FILES
    llanimationstates.cpp
    llbvhloader.cpp
    llcharacter.cpp
    lleditingmotion.cpp
    llgesture.cpp
    llhandmotion.cpp
    llheadrotmotion.cpp
    lljoint.cpp
    lljointsolverrp3.cpp
    llkeyframefallmotion.cpp
    llkeyframemotion.cpp
    llkeyframestandmotion.cpp
    llkeyframewalkmotion.cpp
    llmotioncontroller.cpp
    llmotion.cpp
    llmultigesture.cpp
    llpose.cpp
    lltargetingmotion.cpp
    llvisualparam.cpp
    )

set(llcharacter_HEADER_FILES
    CMakeLists.txt

    llanimationstates.h
    llbvhloader.h
    llbvhconsts.h
    llcharacter.h
    lleditingmotion.h
    llgesture.h
    llhandmotion.h
    llheadrotmotion.h
    lljoint.h
    lljointsolverrp3.h
    lljointstate.h
    llkeyframefallmotion.h
    llkeyframemotion.h
    llkeyframestandmotion.h
    llkeyframewalkmotion.h
    llmotion.h
    llmotioncontroller.h
    llmultigesture.h
    llpose.h
    lltargetingmotion.h
    llvisualparam.h
    )

list(APPEND llcharacter_SOURCE_FILES ${llcharacter_HEADER_FILES})

add_library (llcharacter ${llcharacter_SOURCE_FILES})
target_include_directories( llcharacter  INTERFACE   ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
        llcharacter
        llcommon
        llmath
        llmessage
        llfilesystem
        llxml
    )

if(USE_PRECOMPILED_HEADERS AND ${CMAKE_VERSION} VERSION_GREATER "3.15.0") 
  target_precompile_headers(llcharacter
    PRIVATE
    [["linden_common.h"]]
    )
endif()
