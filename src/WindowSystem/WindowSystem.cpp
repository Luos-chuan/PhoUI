#include "WindowSystem.hpp"
#if defined (_WIN32) || defined (__linux__)
    #define GLFW_INCLUDE_ES2
    #include <GLFW/glfw3.h>
#elif defined (__ANDROID__)
    #include <android/native_window.h>
#endif

namespace SYSTEM {

struct WindowSystem::Impl {
    #if defined (_WIN32) || defined (__linux__)
        GLFWwindow* window = nullptr;
    #elif defined (__ANDROID__)
        ANativeWindow* window = nullptr;
    #endif
};

WindowSystem::WindowSystem() : m_Impl(std::make_unique<Impl>()) {}
WindowSystem::~WindowSystem() {
    #if defined (_WIN32) || defined (__linux__)
        if (m_Impl->window) glfwDestroyWindow(m_Impl->window);
        glfwTerminate();
    #elif defined (__ANDROID__)
        if (m_Impl->window) ANativeWindow_release(m_Impl->window);
    #endif
}

bool WindowSystem::Create(int width, int height, const char* title) {
    #if defined (_WIN32) || defined (__linux__)
        if (!glfwInit()) return false;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        m_Impl->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_Impl->window) {
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(m_Impl->window);
        return true;
    #elif defined (__ANDROID__)
        return true;
    #endif
}

#if defined (__ANDROID__)
void WindowSystem::SetNativeWindow(ANativeWindow* w) {
    if (m_Impl->window) ANativeWindow_release(m_Impl->window);
    m_Impl->window = w;
    if (w) ANativeWindow_acquire(w);
}
ANativeWindow* WindowSystem::GetNativeHandle() const { return m_Impl->window; }
void WindowSystem::PollEvents() {}      // Android 事件由 native_app_glue 驱动
void WindowSystem::SwapBuffers() {}     // 由 EGL 的 eglSwapBuffers 负责
bool WindowSystem::ShouldClose() const { return false; }

#elif defined (_WIN32) || defined (__linux__)

GLFWwindow* WindowSystem::GetNativeHandle() const { return m_Impl->window; }
void WindowSystem::PollEvents() { 
    if (m_Impl->window) glfwPollEvents();
}
void WindowSystem::SwapBuffers() { 
    if (m_Impl->window) glfwSwapBuffers(m_Impl->window);
}
bool WindowSystem::ShouldClose() const {
    return !m_Impl->window || glfwWindowShouldClose(m_Impl->window);
}

#endif
}