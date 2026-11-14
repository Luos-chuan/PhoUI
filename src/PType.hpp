#pragma once
#include <stdexcept>
#include <string>

namespace ui {
    struct PVec2 {
        float x;
        float y;
    };
    struct PVec3 {
        float x, y, z; 
        PVec3(float _x, float _y, float _z)
            :x(_x), y(_y), z(_z)
        {}
        PVec3(std::string HEX) {
            if (!HEX.empty() && HEX[0] == '#') HEX = HEX.substr(1);

            if (HEX.size() != 6 && HEX.size() != 8)
                throw std::invalid_argument("Hex color must be #RRGGBB or #RRGGBBAA");

            auto byte = [&](size_t pos) {
                return static_cast<float>(std::stoi(HEX.substr(pos, 2), nullptr, 16)) / 255.0f;
            };

            x = byte(0);
            y = byte(2);
            z = byte(4);
        }
    };
    struct PVec4 {
        float x, y, z, w;
        PVec4(float _x, float _y, float _z, float _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
        PVec3& xyz() { return *reinterpret_cast<PVec3*>(&x); }
        const PVec3& xyz() const { return *reinterpret_cast<const PVec3*>(&x); }
        PVec4(std::string HEX) {
            if (!HEX.empty() && HEX[0] == '#') HEX = HEX.substr(1);

            if (HEX.size() != 6 && HEX.size() != 8)
                throw std::invalid_argument("Hex color must be #RRGGBB or #RRGGBBAA");

            auto byte = [&](size_t pos) {
                return static_cast<float>(std::stoi(HEX.substr(pos, 2), nullptr, 16)) / 255.0f;
            };

            x = byte(0);
            y = byte(2);
            z = byte(4);
            w = (HEX.size() == 8) ? byte(6) : 1.0f;
        }
    };
    struct PFont {

    };
    struct PSvg {

    };
    
}