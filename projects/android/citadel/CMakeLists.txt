cmake_minimum_required(VERSION 3.4.1)

include_directories(
    ../../../
    ${ANDROID_NDK}/sources/android/native_app_glue
)

add_library(
    citadel

    SHARED

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
)

find_library(
    log-lib
    log
)

find_library(
    android-lib
    android
)

target_link_libraries(
    citadel
    ${android-lib}
    ${log-lib}
)
