#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <iostream>
#include "rce/object_components/object_component.h"

namespace rce {
    class TextObject {
    public:
        Color& getTint();
        float& getFontSize();
        float& getSpacing();
        Vector2& getPosition();
        Font& getFont();
        std::string getText();

        uint32_t& getZOrder();
    private:
        float m_fontSize;
        float m_spacing;
        Color m_tint;
        Vector2 m_position;
        Font m_font;
        std::string m_text;

        uint32_t m_zOrder{UINT_MAX};
    };
}