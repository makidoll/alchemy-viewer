# -*- cmake -*-
# Construct the version and copyright information based on package data.
include(FindAutobuild)

include_guard()

# packages-formatter.py runs autobuild install --versions, which needs to know
# the build_directory, which (on Windows) depends on AUTOBUILD_ADDRSIZE.
# Within an autobuild build, AUTOBUILD_ADDRSIZE is already set. But when
# building in an IDE, it probably isn't. Set it explicitly using
# run_build_test.py.
add_custom_command(OUTPUT packages-info.txt
  COMMENT "Generating packages-info.txt for the about box"
  MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/../autobuild.xml
  DEPENDS ${CMAKE_SOURCE_DIR}/../scripts/packages-formatter.py
          ${CMAKE_SOURCE_DIR}/../autobuild.xml
  COMMAND ${Python3_EXECUTABLE}
          ${CMAKE_SOURCE_DIR}/cmake/run_build_test.py -DAUTOBUILD_ADDRSIZE=${ADDRESS_SIZE} -DAUTOBUILD=${AUTOBUILD_EXECUTABLE}
          ${Python3_EXECUTABLE}
          ${CMAKE_SOURCE_DIR}/../scripts/packages-formatter.py "${VIEWER_CHANNEL}" "${VIEWER_SHORT_VERSION}.${VIEWER_VERSION_REVISION}" "${LIBS_PREBUILT_DIR}" > packages-info.txt
  )
