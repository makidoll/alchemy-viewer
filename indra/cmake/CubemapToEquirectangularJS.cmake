# -*- cmake -*-
use_prebuilt_binary(cubemaptoequirectangular)

# Main JS file
configure_file("${LIBS_PREBUILT_DIR}/js/CubemapToEquirectangular.js" "${CMAKE_SOURCE_DIR}/newview/skins/default/html/common/equirectangular/js/CubemapToEquirectangular.js" COPYONLY)
