#include "PMainApplication.hpp"
#include "../../SkiaBackend/SkiaBackend.hpp"
#include "../../WindowSystem/WindowSystem.hpp"
#include "PWidget/PWidget.hpp"
#include <memory>

namespace ui {
	ui::PMainApplication::PMainApplication()
		:ui::PWidget()
	{
		Type = PWidgetType::MainApplication;
		impl_ = std::make_unique<AppConfig>();
		WindowSystem = std::make_unique<SYSTEM::WindowSystem>();
		Backend = std::make_unique<SYSTEM::SkiaBackend>();
	}
	PMainApplication::~PMainApplication() {

	}
	int PMainApplication::run() {
		if (!WindowSystem->Create(impl_->width, impl_->height, impl_->title.c_str())) {
			return 1;
		}
		Backend->Init(impl_->width, impl_->height);
		while (!WindowSystem->ShouldClose()) {
			Backend->StartFrame(impl_->windowBackgroud);
			Backend->EndFrame(impl_->width, impl_->height);
			WindowSystem->SwapBuffers();
			WindowSystem->PollEvents();
		}
		return 0;
	}

}