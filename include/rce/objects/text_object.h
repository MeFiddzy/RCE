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
        TextObject(std::string text, float fontSize, float spacing, Vector2 position, Color tint = BLACK, Font font = GetFontDefault(), Vector2 origin = {0, 0}):
             m_spacing(spacing), m_font(font), m_text(std::move(text)), m_origin(origin) {
            m_position = position;
            m_scale = fontSize;
            m_color = tint;
        }

        [[nodiscard]] float getSpacing() const;
        [[nodiscard]] const Font& getFont() const;
        [[nodiscard]] const std::string& getText() const;
        [[nodiscard]] const Vector2& getOrigin() const;

        void setSpacing(float spacing);
        void setFont(const Font& font);
        void setText(const std::string& text);
        void setOrigin(const Vector2& origin);

        void draw() override;

    private:
        float m_spacing;
        Vector2 m_origin;
        Font m_font;
        std::string m_text;
    };
}