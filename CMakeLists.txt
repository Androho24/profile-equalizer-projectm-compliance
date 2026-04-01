cmake_minimum_required(VERSION 3.22.1)
project("profileequalizer")

include(FetchContent)

# ============================================================
# libprojectM 4.x — Milkdrop-kompatibler Visualizer
# Erster Build dauert lange (Download + Kompilierung ~10-20 min)
# ============================================================

# Build-Optionen für projectM (BEVOR FetchContent_MakeAvailable)
set(BUILD_TESTING          OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS      OFF CACHE BOOL "" FORCE)
set(ENABLE_GLES            ON  CACHE BOOL "" FORCE)
set(ENABLE_SDL_UI          OFF CACHE BOOL "" FORCE)
set(ENABLE_EMSCRIPTEN      OFF CACHE BOOL "" FORCE)
set(ENABLE_DOXYGEN         OFF CACHE BOOL "" FORCE)
set(ENABLE_THREADING       OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    projectm
    GIT_REPOSITORY https://github.com/projectM-visualizer/projectm.git
    GIT_TAG        v4.1.2
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(projectm)

# ============================================================
# Workaround: version.h wird bei FetchContent-Rebuilds manchmal
# nicht durch configure_file() generiert → manuell erstellen
# ============================================================
set(_pm_version_h "${CMAKE_BINARY_DIR}/_deps/projectm-build/include/projectM-4/version.h")
if(NOT EXISTS "${_pm_version_h}")
    message(STATUS "projectM version.h fehlt — wird manuell erstellt (FetchContent-Workaround)")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/_deps/projectm-build/include/projectM-4")
    file(WRITE "${_pm_version_h}"
"#pragma once
#define PROJECTM_VERSION_MAJOR 4
#define PROJECTM_VERSION_MINOR 1
#define PROJECTM_VERSION_PATCH 2
#define PROJECTM_VERSION_STRING \"4.1.2\"
#define PROJECTM_VERSION_VCS \"v4.1.2\"
")
endif()

# ============================================================
# JNI Bridge Library
# ============================================================

add_library(
    profileequalizer-native
    SHARED
    projectm_bridge.cpp
)

find_library(log-lib log)
find_library(android-lib android)

target_include_directories(profileequalizer-native PRIVATE
    ${projectm_SOURCE_DIR}/src/api/include
)

target_link_libraries(
    profileequalizer-native
    projectM
    ${log-lib}
    ${android-lib}
    EGL
    GLESv3
)

# 16KB Page Alignment — Pflicht für Android 15+ (API 35+, targetSdk 36)
target_link_options(profileequalizer-native PRIVATE "-Wl,-z,max-page-size=16384")

# projectM setzt CMAKE_DEBUG_POSTFIX="d" → libprofileequalizer-natived.so → nicht auffindbar
set_target_properties(profileequalizer-native PROPERTIES DEBUG_POSTFIX "")
