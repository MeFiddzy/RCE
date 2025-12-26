#include "text_box.h"

using namespace rce;

void TextBox::onHover(const Vector2 &mouseLocation, InteractiveObject *) {
    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && m_maxCharacters >= m_value.length() && isAllowed(key))
            m_value = m_value + static_cast<char>(key);

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        m_value = m_value.substr(0, m_value.size() - 1);
    }
}

std::string TextBox::getValue() {
    return m_value;
}

void TextBox::setValue(const std::string &value) {
    m_value = value;
}
