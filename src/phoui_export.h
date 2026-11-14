#pragma once

#if defined(_WIN32)
    #define PUI_PLATFORM_WINDOWS 1
#elif defined(__linux__)
    #define PUI_PLATFORM_LINUX 1
#elif defined(__APPLE__)
    #define PUI_PLATFORM_APPLE 1
#else
    #error "PhoUI: Unsupported platform!"
#endif

#if PUI_PLATFORM_WINDOWS
    #ifdef PHOUI_BUILD_DLL
        #define PHOUI_API __declspec(dllexport)
    #else
        #define PHOUI_API __declspec(dllimport)
    #endif
#else
    // Linux/macOS 默认使用 visibility
    #define PHOUI_API __attribute__((visibility("default")))
#endif