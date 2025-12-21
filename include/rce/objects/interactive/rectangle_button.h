#pragma once
#include <functional>

#include "interactive_object.h"
#include "rce/objects/shape/rectangle_object.h"

namespace rce {
    class RectangleButton : public InteractiveObject {
    public:
        static void onHoverDefault(const Vector2 &mouseLocation) {
        }

        RectangleButton(Vector2 position, Vector2 origin, float rotation, Color color, float width, float height,
                        const std::function<void(const Vector2 &mouseLocation)> &onClick,
                        const std::function<void(const Vector2 &)> &onHover = onHoverDefault) : m_onHover(onHover),
            m_origin(origin), m_width(width), m_height(height), m_onClick(onClick) {
            m_position = position;
            m_rotation = rotation;
            m_color = color;
        };

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

        void onHover(const Vector2 &mouseLocation) const { m_onHover(mouseLocation); }

        void onClick(const Vector2 &mouseLocation) const { m_onClick(mouseLocation); }

    private:
        std::function<void(const Vector2 &)> m_onHover;
        std::function<void(const Vector2 &)> m_onClick;
        Vector2 m_origin;
        float m_width;
        float m_height;
    };
}