cmake_minimum_required(VERSION 3.22)

project(renderd7 VERSION 0.9.5 LANGUAGES CXX)

add_library(renderd7 STATIC
    source/Color.cpp
    source/Error.cpp
    source/FileSystem.cpp
    source/FunctionTrace.cpp
    source/Hardware.cpp
    source/Hid.cpp
    source/Image.cpp
    source/Installer.cpp
    source/internal_db.cpp
    source/lang.cpp
    source/LI7.cpp
    source/Logger.cpp
    source/Memory.cpp
    source/Message.cpp
    source/Net.cpp
    source/nimg.cpp
    source/Overlays.cpp
    source/Render2.cpp
    source/renderd7_logo.cpp
    source/renderd7.cpp
    source/ResultDecoder.cpp
    source/Sheet.cpp
    source/Sound.cpp
    source/Sprite.cpp
    source/SpriteSheetAnimation.cpp
    source/stb.cpp
    source/swr.cpp
    source/Tasks.cpp
    source/Tasks.cpp
    source/ThemeEditor.cpp
    source/thread.cpp
    source/Time.cpp
    source/Timer.cpp
    source/UI7.cpp
)

target_include_directories(renderd7 PUBLIC
    include
    $ENV{DEVKITPRO}/portlibs/3ds/include # Steht leider nicht in den toolchains drinne :/
)
target_compile_definitions(renderd7 PRIVATE _GNU_SOURCE=1) # required for vasprintf (to be removed)
target_link_libraries(renderd7 PUBLIC
    curl mbedtls mbedx509 mbedcrypto # CURL related
    citro2d # Render2 / Draw2 requirement (can't tell what is the current engine :/)
    citro3d # no citro3d no graphics oder so 
    ctru # Base lib for 3ds apps
    z # unused as far as i can tell
    m # base requirement for maths (oder so steh teigentlich in den toolchains schon drinne btw)
)
set_target_properties(renderd7 PROPERTIES
    CMAKE_CXX_STANDARD 17 # Minimum für den momentanen stand
    CMAKE_CXX_STANDARD_REQUIRED true
)