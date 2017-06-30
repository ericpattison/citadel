cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(
    ../../../
    ${ANDROID_NDK}/sources/android/native_app_glue
)

add_library(
    citadel

    STATIC

    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c

    # Castle
    ../../../castle/app/Activity.android.cpp
    ../../../castle/game/Game.cpp
    #../../../castle/PhysicalFile.android.cpp

    # Keep
    ../../../keep/window/OpenGLWindow.android.cpp
    #../../../keep/android/CNativeActivity.cpp

    # Abacus
    #../../../abacus/CQuaternion.cpp
    #../../../abacus/CVector2D.cpp

    # Watchtower
    ../../../watchtower/device/Device.h
    ../../../watchtower/device/OpenGL/OpenGLDevice.h
    ../../../watchtower/device/OpenGL/OpenGLDevice.android.cpp
    ../../../watchtower/Color.h
)

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../dist)
set_target_properties(
    citadel
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY
    "${distribution_DIR}/lib/android/${ANDROID_ABI}"
)