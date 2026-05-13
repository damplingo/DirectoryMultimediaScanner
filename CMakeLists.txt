cmake_minimum_required(VERSION 3.20)
project(
  CppProjectScanner
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PROJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/..)

file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake
  ${PROJECT_DIR}/.cmake/CPM.cmake
)
include(${PROJECT_DIR}/.cmake/CPM.cmake)

CPMAddPackage(
  NAME userver
  GITHUB_REPOSITORY userver-framework/userver
  VERSION 2.6  # или другая версия
)
userver_setup_environment()

add_library(${PROJECT_NAME}_objs OBJECT
    src/TDirectoryScaner.cpp
    src/TDirectoryScaner.h
    src/THttpHandler.h
    src/json.hpp
    src/THttpHandler.cpp   
)
target_link_libraries(${PROJECT_NAME}_objs
  PUBLIC 
  userver::core
)
target_include_directories(${PROJECT_NAME}_objs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)