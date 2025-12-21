#pragma once
#include <functional>

#include "abstract_switch.h"
#include "../interactive_object.h"
#include "rce/objects/shape/rectangle_object.h"

namespace rce {
    class RectangleSwitch : public AbstractSwitch {
    public:
        RectangleSwitch(Vector2 position, Vector2 origin, float rotation, float width, float height,
            Color onColor, Color offColor) :
            m_origin(origin),
            m_width(width), m_height(height) {

            m_position = position;
            m_rotation = rotation;

            m_onColor = onColor;
            m_offColor = offColor;

            m_triggerShape = Rectangle{
                m_position.x,
                m_position.y,
                m_width,
                m_height,
            };

            m_color = offColor;
        }

        [[nodiscard]] Vector2 getOrigin() const {
            return m_origin;
        }

        [[nodiscard]] float getWidth() const {
            return m_width;
        }

        [[nodiscard]] float getHeight() const {
            return m_height;
        }

        void setOrigin(const Vector2 &m_origin) {
            this->m_origin = m_origin;
        }

        void setWidth(const float m_width) {
            this->m_width = m_width;
        }

        void setHeight(const float m_height) {
            this->m_height = m_height;
        }

        void draw() override {
            DrawRectanglePro(
                Rectangle{
                    m_position.x, m_position.y,
                    m_width, m_height,
                },
                m_origin,
                m_rotation,
                m_color
            );
        };
    private:
        Vector2 m_origin;
        float m_width;
        float m_height;
    };
}