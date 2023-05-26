cmake_minimum_required(VERSION 3.2)
project(QtTheme VERSION 1.1.0.1)

find_package(
  Qt5 5.14
  COMPONENTS 
  Core
  Widgets
  REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CXX_STANDARD 11)

# library

aux_source_directory(src CUSTOM_WIDGETS_SOURCE)

add_library(${PROJECT_NAME} STATIC ${CUSTOM_WIDGETS_SOURCE} resource/theme.qrc resource/icon.qrc)

target_include_directories(${PROJECT_NAME} 
                            PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/include
                            Qt5::Core)
                        
target_link_libraries(${PROJECT_NAME} 
                        PRIVATE 
                        Qt5::Core)


# demo binary

set(DEMO_NAME ${PROJECT_NAME}Demo)

aux_source_directory(demo DEMO_SOURCE)

add_executable(${DEMO_NAME} ${DEMO_SOURCE})

target_include_directories(${DEMO_NAME} 
                            PRIVATE
                            ${PROJECT_NAME})

target_link_libraries(${DEMO_NAME} 
                        PRIVATE 
                        ${PROJECT_NAME}
                        Qt5::Widgets)