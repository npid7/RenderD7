cmake_minimum_required(VERSION VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(rederd7 LANGUAGES CXX C VERSION "0.9.5")

file(GLOB_RECURSE CPPFILES source/*.cpp)

add_library(renderd7 ${CPPFILES})
target_include_directories(renderd7 PUBLIC
include
$ENV{DEVKITPRO}/portlibs/3ds/include
)
target_link_libraries(renderd7 PUBLIC citro2d citro3d curl ctru)
target_compile_definitions(renderd7 PRIVATE _GNU_SOURCE=1)

add_subdirectory(rd7tf)

