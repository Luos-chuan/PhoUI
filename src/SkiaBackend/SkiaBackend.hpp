#pragma once
#include "PType.hpp"
#include "phoui_export.h"
#include "shader_s.hpp"
#include <core/SkSurface.h>
#include <core/SkCanvas.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <limits.h>
#include <filesystem>

static std::string getExeDir() {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0) return ".";
    buf[len] = '\0';
    return std::filesystem::path(buf).parent_path().string();
}

namespace SYSTEM {
    class PHOUI_API SkiaBackend {
    public:
        SkiaBackend();
        ~SkiaBackend();
        void Init(int width, int height);
        void StartFrame(ui::PVec4 color);
        void EndFrame(int width, int height);
    private:
        sk_sp<SkSurface> surface;
        GLuint m_Texture = 0;
        GLuint m_VBO = 0;
        SkPixmap pixmap;
        SkCanvas* canvas;
        std::unique_ptr<Shader> m_Shader;
    };
}
