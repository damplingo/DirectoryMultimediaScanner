cmake_minimum_required(VERSION 3.20)
project(
  CppProjectScanner
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc" "src/*.cxx")
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hh" "src/*.hpp" "src/*.hxx")

add_executable(DirectoryMultimediaScanner ${SOURCES} ${HEADERS})
target_compile_options(DirectoryMultimediaScanner PRIVATE "-std=c++20")