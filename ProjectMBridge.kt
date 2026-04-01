package com.androho.profileequalizer.visualization

/**
 * JNI-Bridge zu libprojectM (C++ Seite: projectm_bridge.cpp)
 *
 * Preset-Management: Kotlin verwaltet die .milk-Dateiliste selbst
 * und ruft nativeLoadPresetFile() auf — da 4.1.2 keine eingebaute Playlist hat.
 */
object ProjectMBridge {

    init {
        System.loadLibrary("profileequalizer-native")
    }

    // Build-Proof
    external fun nativeGetVersion(): String
    external fun nativeCheckOpenGLES3(): Boolean

    // Lifecycle — alle Aufrufe müssen im GL-Thread stattfinden
    external fun nativeInit(width: Int, height: Int): Long
    external fun nativeDestroy(handle: Long)
    external fun nativeSetSize(handle: Long, width: Int, height: Int)
    external fun nativeRenderFrame(handle: Long)

    // Audio (thread-safe via projectM intern)
    external fun nativeAddPCMDataMono(handle: Long, pcmData: FloatArray)

    // Preset laden (Pfad zu .milk Datei)
    external fun nativeLoadPresetFile(handle: Long, filePath: String, hardCut: Boolean)
}
