cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(rd7tf LANGUAGES CXX C VERSION "0.9.5")

file(GLOB_RECURSE _CPPFILES source/*.cpp)

add_executable(rd7tf ${_CPPFILES})
target_include_directories(rd7tf PUBLIC
    source
    $ENV{DEVKITPRO}/portlibs/3ds/include
)
target_link_libraries(rd7tf PUBLIC renderd7)

find_program(3DSXTOOL 3dsxtool PATHS $ENV{DEVKITPRO}/tools/bin)
find_program(SMDHTOOL smdhtool PATHS $ENV{DEVKITPRO}/tools/bin)

if(3DSXTOOL AND SMDHTOOL)
    set(SMDH_FILE "${CMAKE_CURRENT_BINARY_DIR}/rd7tf.smdh")
    set(ICON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/app/icon.png")
    add_custom_command(
        OUTPUT ${SMDH_FILE}
        COMMAND ${SMDHTOOL} --create
        "RD7TF"
        "RenderD7 Test Framework"
        "tobid7"
        "${ICON_FILE}"
        "${SMDH_FILE}"
        DEPENDS "${ICON_FILE}"
        COMMENT "Generating SMDH file..."
    )
    add_custom_target(rd7tf_smdh ALL DEPENDS ${SMDH_FILE})
    add_dependencies(rd7tf rd7tf_smdh)
    add_custom_command(
        TARGET rd7tf POST_BUILD
        COMMAND ${3DSXTOOL}
        $<TARGET_FILE:rd7tf>
        "${CMAKE_CURRENT_BINARY_DIR}/rd7tf.3dsx"
        --smdh=${SMDH_FILE}
        --romfs=${CMAKE_CURRENT_SOURCE_DIR}/romfs
        COMMENT "Generating 3DSX file..."
    )
endif()
