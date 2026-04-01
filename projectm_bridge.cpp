#include <jni.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string>
#include <cstring>

#include "projectM-4/projectM.h"
#include "projectM-4/render_opengl.h"   // projectm_opengl_render_frame

#define LOG_TAG "ProjectMBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {

// ============================================================
// Phase 1: Build-Proof
// ============================================================

JNIEXPORT jstring JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeGetVersion(
        JNIEnv *env, jobject) {
    char* v = projectm_get_version_string();
    std::string version = v ? std::string("projectM ") + v : "projectM (version unknown)";
    projectm_free_string(v);
    LOGI("Version: %s", version.c_str());
    return env->NewStringUTF(version.c_str());
}

JNIEXPORT jboolean JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeCheckOpenGLES3(
        JNIEnv *env, jobject) {
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) { LOGE("EGL: kein Display"); return JNI_FALSE; }
    EGLint major, minor;
    if (!eglInitialize(display, &major, &minor)) { LOGE("EGL init failed"); return JNI_FALSE; }
    LOGI("EGL %d.%d OK", major, minor);
    eglTerminate(display);
    return JNI_TRUE;
}

// ============================================================
// Phase 2: Lifecycle
// ============================================================

JNIEXPORT jlong JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeInit(
        JNIEnv *env, jobject,
        jint width, jint height) {

    projectm_handle handle = projectm_create();
    if (!handle) { LOGE("projectm_create() fehlgeschlagen"); return 0L; }

    projectm_set_window_size(handle, (size_t) width, (size_t) height);
    projectm_set_fps(handle, 60);
    projectm_set_beat_sensitivity(handle, 1.0f);

    LOGI("projectM %dx%d initialisiert, handle=%p", width, height, handle);
    return (jlong)(uintptr_t) handle;
}

JNIEXPORT void JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeDestroy(
        JNIEnv *env, jobject, jlong handlePtr) {
    auto handle = (projectm_handle)(uintptr_t) handlePtr;
    if (handle) { projectm_destroy(handle); LOGI("projectM destroyed"); }
}

JNIEXPORT void JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeSetSize(
        JNIEnv *env, jobject, jlong handlePtr, jint width, jint height) {
    auto handle = (projectm_handle)(uintptr_t) handlePtr;
    if (handle) projectm_set_window_size(handle, (size_t) width, (size_t) height);
}

JNIEXPORT void JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeRenderFrame(
        JNIEnv *env, jobject, jlong handlePtr) {
    auto handle = (projectm_handle)(uintptr_t) handlePtr;
    if (handle) projectm_opengl_render_frame(handle);   // korrekter Name
}

// ============================================================
// Phase 3: Audio
// ============================================================

JNIEXPORT void JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeAddPCMDataMono(
        JNIEnv *env, jobject, jlong handlePtr, jfloatArray pcmData) {
    auto handle = (projectm_handle)(uintptr_t) handlePtr;
    if (!handle) return;
    jsize count = env->GetArrayLength(pcmData);
    jfloat *data = env->GetFloatArrayElements(pcmData, nullptr);
    if (data) {
        projectm_pcm_add_float(handle, data, (unsigned int) count, PROJECTM_MONO);
        env->ReleaseFloatArrayElements(pcmData, data, JNI_ABORT);
    }
}

// ============================================================
// Phase 4: Preset-Management (Kotlin verwaltet Liste, lädt Datei)
// ============================================================

JNIEXPORT void JNICALL
Java_com_androho_profileequalizer_visualization_ProjectMBridge_nativeLoadPresetFile(
        JNIEnv *env, jobject, jlong handlePtr, jstring filePath, jboolean hardCut) {
    auto handle = (projectm_handle)(uintptr_t) handlePtr;
    if (!handle) return;
    const char *path = env->GetStringUTFChars(filePath, nullptr);
    if (path) {
        projectm_load_preset_file(handle, path, (bool) hardCut);
        LOGI("Preset geladen: %s", path);
        env->ReleaseStringUTFChars(filePath, path);
    }
}

} // extern "C"
