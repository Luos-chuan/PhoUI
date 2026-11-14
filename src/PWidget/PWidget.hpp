#pragma once 
#include <memory>
#include <unordered_map>
#include <utility>
#include <variant>
#include <string>
#include <vector>
#include "../PType.hpp"
#include "../phoui_export.h"

namespace ui {
    class PWidget;
    enum class PStyleTypeName
    {
        //* This is Can be changed Part
        Width      , // float
        Height     , // float
        Alpha      , // float
        Name       , // std::string
        Visible    , // bool
        Enabled    , // bool
        Font       , // PFont

        //* This is Can't be changed Part
        Position  , // PVec2
        Parent    , // PWidget*
        Childrens   // std::vector<PWidget*>

    };

    enum class PWidgetType {
        Widget,
        MainApplication,
        Layout,
        GridLayout,
        Buttom,
        ImageBox,
        Label,
        LineEdit
    };

    using PStyleType           = std::variant<float, bool, std::string, std::vector<PWidget*>, ui::PVec2, ui::PFont, PWidget*>;
    using PStyleTypeInputValue = std::pair<PStyleTypeName, PStyleType>;

    struct PWidgetTypeGroup {
        std::unordered_map<PStyleTypeName, PStyleType> Value;
        PStyleType& operator[](PStyleTypeName name) {
            return Value[name];
        }
        const PStyleType& operator[](PStyleTypeName name) const {
            return Value.at(name);
        }
    };
}


namespace ui {

    class PHOUI_API PWidget {
    public:

        PWidget();
        ~PWidget();
        virtual void SetStyleSheet(std::vector<PStyleTypeInputValue> Input);
        void SetParent(PWidget* parent) {
            (*StyleGroup)[PStyleTypeName::Parent] = parent;
        }
        void SetPos(PVec2 aPos) {
            (*StyleGroup)[PStyleTypeName::Position] = aPos;
        }
        void AddChild(PWidget* children) {
            auto& slot = (*StyleGroup)[PStyleTypeName::Childrens];

            // 如果 slot 还不是 vector<PWidget*>，先初始化成空 vector
            if (!std::holds_alternative<std::vector<PWidget*>>(slot)) {
                slot = std::vector<PWidget*>{};
            }

            std::get<std::vector<PWidget*>>(slot).push_back(children);
        }
    private:
        std::unique_ptr<PWidgetTypeGroup> StyleGroup;
    protected:
        PWidgetType Type;
    };
}