#include "text_object.h"

using namespace rce;

Vector2 &TextObject::getPosition() {
    return m_position;
}

float &TextObject::getFontSize() {
    return m_fontSize;
}

Color &TextObject::getTint() {
    return m_tint;
}

Font &TextObject::getFont() {
    return m_font;
}

std::string TextObject::getText() {
    return m_text;
}

float &TextObject::getSpacing() {
    return m_spacing;
}

uint32_t &TextObject::getZOrder() {
    return m_zOrder;
}
