// phoui/EntryPoint.hpp
#pragma once

#include "phoui_export.h"      // PHOUI_API 导出宏
#include "PWidget/PMainApplication/PMainApplication.hpp"

namespace phoui {

// 宿主提供窗口的两种模式
struct PhouiDesc {
    void*  nativeWindow;      // GLFWwindow* / HWND / wl_surface 等
    int    width;
    int    height;
    const char* title;
    // 渲染后端描述：OpenGL 或 Vulkan 句柄
    enum class Backend { OpenGL, Vulkan } backend;
    void*  glContext;         // OpenGL：宿主创建的 context（可选）
    void*  vkInstance;        // Vulkan：宿主创建的 instance（可选）
    void*  vkDevice;          // Vulkan：宿主创建的 device（可选）
};

class PHOUI_API PhouiContext;   // 不透明句柄

} // namespace phoui

extern "C" {

// 模式 A：UI 拥有主循环，阻塞直到窗口关闭
PHOUI_API int PhouiRun(int argc, char** argv);

// 模式 B：宿主拥有主循环，逐帧驱动
PHOUI_API phoui::PhouiContext* PhouiCreate(const phoui::PhouiDesc* desc);
PHOUI_API void PhouiTick(phoui::PhouiContext* ctx);
PHOUI_API void PhouiDestroy(phoui::PhouiContext* ctx);

// 由 PHOUI_ENTRY 生成的工厂，库内部查找/链接
PHOUI_API ui::PMainApplication* PhouiCreateMainWidget();

}