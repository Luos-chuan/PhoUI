#pragma once
#include "../phoui_export.h"
#include <memory>

#if defined(__ANDROID__)
struct ANativeWindow;
#else
struct GLFWwindow;
#endif

namespace SYSTEM {

class PHOUI_API WindowSystem {
public:
    WindowSystem();
    ~WindowSystem();

    // 创建窗口，返回是否成功
    bool Create(int width, int height, const char* title);

    // 获取原生句柄（平台相关）
#if defined(__ANDROID__)
    ANativeWindow* GetNativeHandle() const;
#else
    GLFWwindow* GetNativeHandle() const;
#endif

    // 每帧调用
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;   // PIMPL 隐藏平台细节
};

}