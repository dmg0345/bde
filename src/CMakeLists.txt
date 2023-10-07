# Create library target.
add_library(bde ${CFG_LIB_BUILD_TYPE})

# Set installation directories.
install(TARGETS bde
        RUNTIME DESTINATION "${CMAKE_INSTALL_RUNTIMEDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

# Add Base64 and Base64URL encoders and decoders.
add_subdirectory("base64")

## Source files ########################################################################################################
# Collect source files.
set(SOURCES_BDE
    ${SOURCES_BDE_BASE64}
    CACHE INTERNAL ""
)
target_sources(bde PRIVATE ${SOURCES_BDE})

## Includes ############################################################################################################
# Collect private include directories and add them to target, this will only be visible within the library.
set(INCLUDE_DIRS_BDE
    ${INCLUDE_DIRS_BDE_BASE64}
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    CACHE INTERNAL ""
)
target_include_directories(bde PRIVATE ${INCLUDE_DIRS_BDE})

# Collect interface include directories and add them to target, these will only be visible by the application.
set(INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)
target_include_directories(bde INTERFACE ${INCLUDE_DIRS})

## Distributable includes ##############################################################################################
# Variables to paths for convenience.
set(BDE_SRC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc/bde")
set(BDE_INSTALL_ROOT_DIR "${CMAKE_INSTALL_INCLUDEDIR}/bde")

# Common include files.
install(FILES "${BDE_SRC_ROOT_DIR}/bde.h" DESTINATION "${BDE_INSTALL_ROOT_DIR}")
install(FILES
    "${BDE_SRC_ROOT_DIR}/other/version.h"
    "${BDE_SRC_ROOT_DIR}/other/commons.h"
    DESTINATION "${BDE_INSTALL_ROOT_DIR}/other"
)

# Base64 and Base64URL files.
install(FILES
    "${BDE_SRC_ROOT_DIR}/base64/decode.h"
    "${BDE_SRC_ROOT_DIR}/base64/encode.h"
    "${BDE_SRC_ROOT_DIR}/base64/url_decode.h"
    "${BDE_SRC_ROOT_DIR}/base64/url_encode.h"
    DESTINATION "${BDE_INSTALL_ROOT_DIR}/base64"
)
