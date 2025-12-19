#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <iostream>
#include "rce/object_components/object_component.h"
#include "abstract_object.h"

namespace rce {
    class TextObject: public AbstractObject{
    public:
        TextObject(float fontSize, float spacing, Color tint, Vector2 position, Font font, std::string text):
            m_fontSize(fontSize), m_spacing(spacing), m_tint(tint), m_font(font), m_text(std::move(text)) {
            m_position = position;
        }

        [[nodiscard]] const Color& getTint() const;
        [[nodiscard]] float getFontSize() const;
        [[nodiscard]] float getSpacing() const;
        [[nodiscard]] const Font& getFont() const;
        [[nodiscard]] const std::string& getText() const;

        void setTint(const Color& tint);
        void setFontSize(float fontSize);
        void setSpacing(float spacing);
        void setFont(const Font& font);
        void setText(const std::string& text);

    private:
        float m_fontSize;
        float m_spacing;
        Color m_tint;
        Font m_font;
        std::string m_text;
    };
}