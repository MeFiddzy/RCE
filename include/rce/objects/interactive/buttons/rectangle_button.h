#pragma once
#include <functional>

#include "abstract_button.h"
#include "../interactive_object.h"
#include "rce/objects/shape/rectangle_object.h"

namespace rce {
    class RectangleButton : public AbstractButton {
    public:
        RectangleButton(Vector2 position, Vector2 origin, float rotation, Color color, float width, float height,
                        const std::function<void(const Vector2&, AbstractButton*)> &onClick = emptyFunc,
                        const std::function<void(const Vector2&, AbstractButton*)> &onButtonDown = emptyFunc,
                        const std::function<void(const Vector2&, AbstractButton*)> &onRelease = emptyFunc,
                        const std::function<void(const Vector2&, AbstractButton*)> &onHover = emptyFunc) :
            m_origin(origin),
            m_width(width), m_height(height) {

            m_position = position;
            m_rotation = rotation;
            m_color = color;

            m_onClick = onClick;
            m_onRelease = onRelease;
            m_onHover = onHover;
            m_onButtonDown = onButtonDown;


            m_triggerShape = Rectangle{
                m_position.x,
                m_position.y,
                m_width,
                m_height,
            };
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

        void setWidth(float m_width) {
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