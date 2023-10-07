# Base64 decode tests.
define_test_suite(test_base64_decode)
target_sources(test_base64_decode PRIVATE ${SOURCES_BDE})
target_include_directories(test_base64_decode PRIVATE ${INCLUDE_DIRS_BDE})
target_sources(test_base64_decode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_base64_decode.c")
target_include_directories(test_base64_decode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Base64 encode tests.
define_test_suite(test_base64_encode)
target_sources(test_base64_encode PRIVATE ${SOURCES_BDE})
target_include_directories(test_base64_encode PRIVATE ${INCLUDE_DIRS_BDE})
target_sources(test_base64_encode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_base64_encode.c")
target_include_directories(test_base64_encode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Base64URL decode tests.
define_test_suite(test_base64url_decode)
target_sources(test_base64url_decode PRIVATE ${SOURCES_BDE})
target_include_directories(test_base64url_decode PRIVATE ${INCLUDE_DIRS_BDE})
target_sources(test_base64url_decode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_base64url_decode.c")
target_include_directories(test_base64url_decode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Base64URL encode tests.
define_test_suite(test_base64url_encode)
target_sources(test_base64url_encode PRIVATE ${SOURCES_BDE})
target_include_directories(test_base64url_encode PRIVATE ${INCLUDE_DIRS_BDE})
target_sources(test_base64url_encode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_base64url_encode.c")
target_include_directories(test_base64url_encode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
