#include "PWidget.hpp"
#include "PType.hpp"
#include <memory>
#include <string>

namespace ui {
    PWidget::PWidget()
        :Type(PWidgetType::Widget)
    {
        StyleGroup = std::make_unique<PWidgetTypeGroup>();
        (*StyleGroup)[PStyleTypeName::Width]     = 10.0f;
        (*StyleGroup)[PStyleTypeName::Height]    = 6.18f;
        (*StyleGroup)[PStyleTypeName::Name]      = std::string("widget");
        (*StyleGroup)[PStyleTypeName::Alpha]     = 1.0f;
        (*StyleGroup)[PStyleTypeName::Enabled]   = true;
        (*StyleGroup)[PStyleTypeName::Visible]   = true;
        (*StyleGroup)[PStyleTypeName::Font]      = PFont();
        (*StyleGroup)[PStyleTypeName::Childrens] = {};
        (*StyleGroup)[PStyleTypeName::Parent]    = nullptr;
        (*StyleGroup)[PStyleTypeName::Position]  = PVec2(0, 0);

    }
    PWidget::~PWidget() {

    }
    void PWidget::SetStyleSheet(std::vector<PStyleTypeInputValue> Input) {
        for (PStyleTypeInputValue a : Input) {
            switch (a.first) {
                case PStyleTypeName::Width:
                    (*StyleGroup)[PStyleTypeName::Width] = std::get<float>(a.second);
                    break;
                case PStyleTypeName::Height:
                    (*StyleGroup)[PStyleTypeName::Height] = std::get<float>(a.second);
                    break;
                case PStyleTypeName::Name:
                    (*StyleGroup)[PStyleTypeName::Name] = std::get<std::string>(a.second);
                    break;
                case PStyleTypeName::Alpha:
                    (*StyleGroup)[PStyleTypeName::Alpha] = std::get<float>(a.second);
                    break;
                case PStyleTypeName::Enabled:
                    (*StyleGroup)[PStyleTypeName::Enabled] = std::get<bool>(a.second);
                    break;
                case PStyleTypeName::Visible:
                    (*StyleGroup)[PStyleTypeName::Visible]  = std::get<bool>(a.second);
                    break;
                case PStyleTypeName::Font:
                    (*StyleGroup)[PStyleTypeName::Font]  = std::get<PFont>(a.second);
                    break;
                default:
                    break;
            }
        }
    }
}