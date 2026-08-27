cmake_minimum_required(VERSION 3.22)

project(renderd7 VERSION 0.9.6 LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo" CACHE STRING "Available build types" FORCE)

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
    source/ThemeEditor.cpp
    source/thread.cpp
    source/Time.cpp
    source/Timer.cpp
    source/UI7.cpp
)

target_include_directories(renderd7 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $ENV{DEVKITPRO}/portlibs/3ds/include # Steht leider nicht in den toolchains drinne :/
)
target_compile_options(renderd7 PRIVATE -Wno-psabi)
target_link_libraries(renderd7 PUBLIC
    curl mbedtls mbedx509 mbedcrypto # CURL related
    citro2d # Render2 / Draw2 requirement (can't tell what is the current engine :/)
    citro3d # no citro3d no graphics oder so 
    ctru # Base lib for 3ds apps
    z # unused as far as i can tell
    m # base requirement for maths (oder so steh teigentlich in den toolchains schon drinne btw)
)
set_target_properties(renderd7 PROPERTIES
    CXX_STANDARD 20 # Minimum für den momentanen stand
    CXX_STANDARD_REQUIRED true
    DEBUG_POSTFIX "d"
    MINSIZEREL_POSTFIX "ms"
    RELWITHDEBINFO_POSTFIX "rd"
)
target_compile_definitions(renderd7 PRIVATE
    "RD7_VERSION=(($<IF:$<BOOL:${PROJECT_VERSION_MAJOR}>,${PROJECT_VERSION_MAJOR},0> << 24) | \
                  ($<IF:$<BOOL:${PROJECT_VERSION_MINOR}>,${PROJECT_VERSION_MINOR},0> << 16) | \
                  ($<IF:$<BOOL:${PROJECT_VERSION_PATCH}>,${PROJECT_VERSION_PATCH},0> << 8)  | \
                   $<IF:$<BOOL:${PROJECT_VERSION_TWEAK}>,${PROJECT_VERSION_TWEAK},0>)"
)

include(GNUInstallDirs)
install(TARGETS renderd7
    EXPORT renderd7-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT renderd7-targets
    FILE renderd7Targets.cmake
    NAMESPACE renderd7::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/renderd7
)

set(CPACK_GENERATOR "TZST") # cause i like .tar.zst
include(CPack)
