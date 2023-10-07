########################################################################################################################
# This file tags all the application, library and test files with data such as the project author and timestamps.
########################################################################################################################

# Check if tagging filenames only.
if (${CFG_TAG} STREQUAL "FILENAMES_ONLY")
    # Loop each file in the project source files and silently tag their filename if not already tagged.
    foreach(PROJECT_SOURCE_FILE ${PROJECT_SOURCE_FILES})
        # Fetch filename component.
        get_filename_component(PROJECT_FILENAME ${PROJECT_SOURCE_FILE} NAME)
        # Replace just the @VALUE@ tags.
        message(STATUS "Tagging '${PROJECT_SOURCE_FILE}' if not already tagged...")
        configure_file("${PROJECT_SOURCE_FILE}" "${PROJECT_SOURCE_FILE}" @ONLY NEWLINE_STYLE CRLF)
    endforeach()
elseif(${CFG_TAG} STREQUAL "ON")
    # Print a summary of relevant variables.
    message(STATUS "########## Relevant Tagging Values ######################")
    message(STATUS "PROJECT_NAME_LOWERCASE: '${PROJECT_NAME_LOWERCASE}'")
    message(STATUS "PROJECT_AUTHOR: '${PROJECT_AUTHOR}'")
    message(STATUS "PROJECT_CONTACT: '${PROJECT_CONTACT}'")
    message(STATUS "PROJECT_BUILD_TIMESTAMP_UTC: '${PROJECT_BUILD_TIMESTAMP_UTC}'")
    message(STATUS "PROJECT_VERSION: '${PROJECT_VERSION}'")
    message(STATUS "PROJECT_VCS_HASH: '${PROJECT_VCS_HASH}'")
    message(STATUS "#########################################################")

    # Loop each file in the project source files and tag it.
    foreach(PROJECT_SOURCE_FILE ${PROJECT_SOURCE_FILES})
        # Fetch the filename for the current file.
        get_filename_component(PROJECT_FILENAME ${PROJECT_SOURCE_FILE} NAME)
        # Replace tags in the file with known values.
        message(STATUS "Tagging '${PROJECT_SOURCE_FILE}' if not already tagged...")
        configure_file("${PROJECT_SOURCE_FILE}" "${PROJECT_SOURCE_FILE}" NEWLINE_STYLE CRLF)
    endforeach()
else()
    message(FATAL_ERROR "CFG_TAG value '${CFG_TAG}' is not a valid value.")
endif()
