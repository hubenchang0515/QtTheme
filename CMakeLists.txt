cmake_minimum_required(VERSION 3.5)
project(QtTheme VERSION 1.0.2)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(USE_3RDPARTY "Use the libraries in 3rdparty to build, or use the system libraries." ON)

get_property(BUILD_SHARED_LIBS GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)

if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif (POLICY CMP0077)

if (USE_3RDPARTY)
  add_subdirectory(3rdparty EXCLUDE_FROM_ALL)
endif(USE_3RDPARTY)

if(WIN32)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(Qt6 COMPONENTS Core Widgets UiTools QUIET)

if (NOT Qt6_FOUND)
  find_package(Qt5 COMPONENTS Core Widgets UiTools REQUIRED)
endif (NOT Qt6_FOUND)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CXX_STANDARD 11)

file(GLOB QTTHEME_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/QtTheme/*.h")
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src/QtTheme" LIB_SOURCE)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src/" EXEC_SOURCE)

if (Qt6_FOUND)
  add_library(${PROJECT_NAME}_lib ${LIB_SOURCE} src/resource/QtTheme.qrc)
  qt_add_executable(${PROJECT_NAME} ${EXEC_SOURCE})
else()
  add_library(${PROJECT_NAME}_lib ${LIB_SOURCE} src/resource/QtTheme.qrc)
  add_executable(${PROJECT_NAME} ${EXEC_SOURCE})
endif()

set_target_properties(${PROJECT_NAME}_lib
                      PROPERTIES
                      OUTPUT_NAME ${PROJECT_NAME}
                      PUBLIC_HEADER "${QTTHEME_HEADER}")

target_include_directories(${PROJECT_NAME}_lib PUBLIC Qt::Core)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib Qt::Core Qt::Widgets Qt::UiTools zip "${CMAKE_CURRENT_SOURCE_DIR}/src/")

target_link_libraries(${PROJECT_NAME}_lib PRIVATE Qt::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib Qt::Core Qt::Widgets Qt::UiTools zip)

if (WIN32)
  target_link_options(${PROJECT_NAME} PRIVATE "$<$<AND:$<STREQUAL:$<CXX_COMPILER_ID>,MSVC>,$<STREQUAL:$<CONFIG>,Release>>:/SUBSYSTEM:windows;/ENTRY:mainCRTStartup>")
  target_link_options(${PROJECT_NAME} PRIVATE "$<$<AND:$<STREQUAL:$<CXX_COMPILER_ID>,GNU>,$<STREQUAL:$<CONFIG>,Release>>:-mwindows>")
endif(WIN32)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
