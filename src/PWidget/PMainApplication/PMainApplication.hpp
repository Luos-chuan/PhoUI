#pragma once
#include "../PWidget.hpp"
#include "../../phoui_export.h"
#include "PType.hpp"
#include <memory>
#include <string>
namespace SYSTEM {
    class SkiaBackend;
    class WindowSystem;
}
namespace ui {

enum class Backend { Vulkan, GLES };

struct AppConfig {
    int width = 1280;
    int height = 720;
    PVec4 windowBackgroud = PVec4(0 ,0 ,0 ,1);
    std::string title = "PhoUI Application";
};
class PHOUI_API PMainApplication : public ui::PWidget {
public:
    PMainApplication();
    virtual ~PMainApplication();

    // 阻塞运行，直到窗口关闭
    int run();

    // 窗口访问（只读，不能替换窗口）
    void* nativeWindow() const;

protected:
    void SetTitle(std::string title) {
        impl_->title = title;
    }
    void SetWindowSize(ui::PVec2 size) {
        impl_->width = size.x;
        impl_->width = size.y;
    }
    void SetBackground(PVec3 color) {
        impl_->windowBackgroud.xyz() = color;
    }

private:
    std::unique_ptr<AppConfig> impl_;
    std::unique_ptr<SYSTEM::SkiaBackend> Backend;
    std::unique_ptr<SYSTEM::WindowSystem> WindowSystem;
    void SetStyleSheet(std::vector<PStyleTypeInputValue> Input) override {
        PWidget::SetStyleSheet(Input);
    }
};

} // namespace phoui