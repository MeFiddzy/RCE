#pragma once
#include "../abstract_object.h"

namespace rce {
    class RectangleObject : public AbstractObject {
    public:
        RectangleObject(Vector2 position, Vector2 origin, float rotation, Color color, float width, float height) :
        m_origin(origin), m_height(height), m_width(width) {
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

        void setHeight(float m_height) {
            this->m_height = m_height;
        }

        void draw() override;

    private:
        Vector2 m_origin;
        float m_width;
        float m_height;
    };
}
