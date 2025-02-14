cmake_minimum_required(VERSION 3.2)
project(QtTheme VERSION 1.1.0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(USE_3RDPARTY "Use the libraries in 3rdparty to build, or use the system libraries." ON)

if (USE_3RDPARTY)
  add_subdirectory(3rdparty EXCLUDE_FROM_ALL)
endif(USE_3RDPARTY)

if(WIN32)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  add_link_options("$<$<AND:$<STREQUAL:$<CXX_COMPILER_ID>,MSVC>,$<STREQUAL:$<CONFIG>,Release>>:/SUBSYSTEM:windows;/ENTRY:mainCRTStartup>")
  add_link_options("$<$<AND:$<STREQUAL:$<CXX_COMPILER_ID>,GNU>,$<STREQUAL:$<CONFIG>,Release>>:-mwindows>")
endif()

find_package(Qt6 COMPONENTS Core Widgets UiTools QUIET)

if (NOT Qt6_FOUND)
  find_package(Qt5 COMPONENTS Core Widgets UiTools REQUIRED)
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

target_include_directories(${PROJECT_NAME} PUBLIC Qt::Core Qt::Widgets Qt::UiTools zip)
                        
target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets Qt::UiTools zip)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})