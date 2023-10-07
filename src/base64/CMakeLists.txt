## Sources #############################################################################################################
# Collect sources for Base64 and Base64URL.
set(SOURCES_BDE_BASE64
    "${CMAKE_CURRENT_SOURCE_DIR}/base64.c"
    PARENT_SCOPE
)

## Includes ############################################################################################################
# Collect private include directories for Base64 and Base64URL.
set(INCLUDE_DIRS_BDE_BASE64
    "${CMAKE_CURRENT_SOURCE_DIR}"
    PARENT_SCOPE
)
