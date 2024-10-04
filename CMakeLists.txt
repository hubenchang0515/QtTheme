cmake_minimum_required(VERSION 3.2)
project(QtTheme VERSION 1.1.0.1)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(3rdparty EXCLUDE_FROM_ALL)

find_package(Qt6 COMPONENTS Core Widgets QUIET)

if (NOT Qt6_FOUND)
  find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
endif (NOT Qt6_FOUND)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CXX_STANDARD 11)

aux_source_directory(src CUSTOM_WIDGETS_SOURCE)

if (Qt6_FOUND)
  qt_add_executable(${PROJECT_NAME} ${CUSTOM_WIDGETS_SOURCE} src/resource/theme.qrc src/resource/icon.qrc)
else()
  add_executable(${PROJECT_NAME} ${CUSTOM_WIDGETS_SOURCE} src/resource/theme.qrc src/resource/icon.qrc)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC Qt::Core Qt::Widgets zip)
                        
target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets zip)