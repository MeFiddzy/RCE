#include "text_object.h"

using namespace rce;

float TextObject::getSpacing() const {
    return m_spacing;
}

const Font &TextObject::getFont() const {
    return m_font;
}

const std::string &TextObject::getText() const {
    return m_text;
}

void TextObject::setSpacing(float spacing) {
    m_spacing = spacing;
}

void TextObject::setFont(const Font &font) {
    m_font = font;
}

void TextObject::setText(const std::string &text) {
    m_text = text;
}

void TextObject::draw() {
    DrawTextPro(
            m_font,
            m_text.data(),
            m_position,
            m_origin,
            m_rotation,
            m_scale,
            m_spacing,
            m_color
    );
}

const Vector2 &TextObject::getOrigin() const {
    return m_origin;
}

void TextObject::setOrigin(const Vector2 &origin) {
    m_origin = origin;
}
