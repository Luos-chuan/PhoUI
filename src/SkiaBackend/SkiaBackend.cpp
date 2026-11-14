#include "SkiaBackend.hpp"
#include "PType.hpp"
#include <GLES2/gl2.h>

namespace SYSTEM {
    SkiaBackend::SkiaBackend() {

    }
    SkiaBackend::~SkiaBackend() {

    }
    
    void SkiaBackend::Init(int width, int height) {
        // 创建 CPU 光栅表面
        surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));
        if (!surface) {
            // 处理失败
            return;
        }
        canvas = surface->getCanvas();

        // 纹理
        glGenTextures(1, &m_Texture);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // 全屏 quad：两个三角形，每个顶点 (x, y, u, v)
        const float verts[] = {
            -1, -1, 0, 1,
            1, -1, 1, 1,
            1,  1, 1, 0,
            -1, -1, 0, 1,
            1,  1, 1, 0,
            -1,  1, 0, 0,
        };
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

        auto exeDir = getExeDir();
        std::string vertPath = exeDir + "/shaders/quad.vert";
        std::string fragPath = exeDir + "/shaders/quad.frag";
        m_Shader = std::make_unique<Shader>(vertPath.c_str(), fragPath.c_str());
    }
    void SkiaBackend::StartFrame(ui::PVec4 color) {

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(color.x, color.y, color.z, color.w);
    }
    void SkiaBackend::EndFrame(int width, int height) {
        
        if (!surface->peekPixels(&pixmap)) {
            // 处理失败
        }
        const void* pixels = pixmap.addr();
        size_t rowBytes = pixmap.rowBytes();

        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, pixmap.addr());

        m_Shader->use();

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        GLint aPos = glGetAttribLocation(m_Shader->ID, "aPos");
        GLint aUV  = glGetAttribLocation(m_Shader->ID, "aUV");
        glEnableVertexAttribArray(aPos);
        glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(aUV);
        glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glUniform1i(glGetUniformLocation(m_Shader->ID, "uTex"), 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        
    }
}