# Building the Native Library — libprojectM Integration

This document describes how to rebuild the `profileequalizer-native` shared library
that links against libprojectM v4.1.2.

## Prerequisites

| Tool | Version |
|------|---------|
| Android Studio | Hedgehog or newer |
| NDK | 26.1.10909125 |
| CMake | 3.22.1 or newer |
| Git | Any recent version |

Install the NDK and CMake via **Android Studio → SDK Manager → SDK Tools**.

## Application-Specific Source Files

The only application-specific code (the "Application" portion per LGPL-2.1 §6) is:

| File | Description |
|------|-------------|
| `app/src/main/cpp/projectm_bridge.cpp` | JNI bridge between Android/Java and libprojectM C API |
| `app/src/main/cpp/CMakeLists.txt` | CMake build script; fetches libprojectM v4.1.2 via FetchContent |

## Build Steps

1. **Clone this repository:**
   ```bash
   git clone https://github.com/YOUR_USERNAME/ProfileEqualizer.git
   cd ProfileEqualizer
   ```

2. **Enable the native build in `app/build.gradle`:**  
   Uncomment the `externalNativeBuild` block:
   ```groovy
   externalNativeBuild {
       cmake {
           path "src/main/cpp/CMakeLists.txt"
           version "3.22.1"
       }
   }
   ```

3. **Build the debug APK** (first build downloads + compiles libprojectM, ~10–20 min):
   ```bash
   ./gradlew assembleLiteDebug
   ```
   The resulting `.so` is at:
   ```
   app/build/intermediates/cxx/<variant>/.../lib/<abi>/libprofilequalizer-native.so
   ```

## How libprojectM is Fetched

The CMake script uses `FetchContent_Declare` to download libprojectM directly from
the upstream GitHub repository at the exact tag `v4.1.2`:

```cmake
FetchContent_Declare(
    projectm
    GIT_REPOSITORY https://github.com/projectM-visualizer/projectm.git
    GIT_TAG        v4.1.2
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(projectm)
```

No source modifications are made to libprojectM. The library is compiled with these
options (to reduce binary size and fit the Android environment):

| CMake Option | Value | Reason |
|-------------|-------|--------|
| `BUILD_TESTING` | OFF | No tests needed |
| `BUILD_SHARED_LIBS` | OFF | Static linking into JNI bridge |
| `ENABLE_GLES` | ON | Android uses OpenGL ES |
| `ENABLE_SDL_UI` | OFF | No SDL on Android |
| `ENABLE_EMSCRIPTEN` | OFF | Not targeting WebAssembly |
| `ENABLE_DOXYGEN` | OFF | No documentation generation |
| `ENABLE_THREADING` | OFF | Single-threaded rendering |

## Supported ABIs

Built for all ABIs supported by the app: `arm64-v8a`, `armeabi-v7a`, `x86`, `x86_64`.

## 16KB Page Alignment

Android 15+ (API 35+) requires 16KB page alignment. This is enforced via:
```cmake
target_link_options(profileequalizer-native PRIVATE "-Wl,-z,max-page-size=16384")
```
