#include "text_object.h"

using namespace rce;

const Color &TextObject::getTint() const {
    return m_tint;
}

float TextObject::getSpacing() const {
    return m_spacing;
}

float TextObject::getFontSize() const {
    return m_fontSize;
}

const Font &TextObject::getFont() const {
    return m_font;
}

const std::string &TextObject::getText() const {
    return m_text;
}

void TextObject::setTint(const Color &tint) {
    m_tint = tint;
}

void TextObject::setFontSize(float fontSize) {
    m_fontSize = fontSize;
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
