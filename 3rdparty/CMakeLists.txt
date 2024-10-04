add_subdirectory(zlib EXCLUDE_FROM_ALL)
add_library(ZLIB::ZLIB ALIAS zlib)

file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/zlib/zconf.h.included ${CMAKE_CURRENT_SOURCE_DIR}/zlib/zconf.h)

# fix export(TARGETS zip ...)
export(TARGETS zlib FILE "${PROJECT_BINARY_DIR}/zlib-targets.cmake")

# fix install(EXPORT libzip-targets ...)
install(TARGETS zlib EXPORT zlib-targets)
install(EXPORT zlib-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zlib)

# fix find_package(ZLIB)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(ENABLE_BZIP2 OFF CACHE BOOL "")
SET(ENABLE_LZMA OFF CACHE BOOL "")
SET(ENABLE_ZSTD OFF CACHE BOOL "")
SET(BUILD_REGRESS OFF CACHE BOOL "")

add_subdirectory(libzip EXCLUDE_FROM_ALL)
target_include_directories(zip PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/zlib>)