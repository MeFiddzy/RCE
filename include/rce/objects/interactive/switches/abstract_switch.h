#pragma once
#include "../interactive_object.h"

namespace rce {
    class AbstractSwitch : public InteractiveObject {
    public:
        void onClick(const Vector2 &mouseLocation, InteractiveObject *) override {
            m_value = !m_value;

            m_color = m_value == true ? m_onColor : m_offColor;
        }

        [[nodiscard]] bool getValue() const { return m_value; }

        void setValue(const bool value) {
            m_value = value;

            m_color = m_value == true ? m_onColor : m_offColor;
        }

    protected:
        bool m_value = false;

        Color m_onColor{}, m_offColor{};
    };
}
