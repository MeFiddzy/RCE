#pragma once
#include "text_box.h"
#include "rce/objects/interactive/interactive_object.h"

namespace rce {
    class RectangleTextBox : public TextBox {
    public:
        RectangleTextBox(Vector2 position, Vector2 origin, float rotation, Color color, float width, float height, int maxChars) :
        m_origin(origin), m_height(height), m_width(width) {
            m_position = position;
            m_rotation = rotation;
            m_color = color;
            m_maxCharacters = maxChars;

            m_triggerShape = {position.x, position.y, width, height};
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

        [[nodiscard]] float getMaxCharacters() const {
            return m_maxCharacters;
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

        void setMaxChars(int x) {
            m_maxCharacters = x;
        }

        void draw() override {
            DrawRectanglePro(
                Rectangle {
                    m_position.x, m_position.y,
                    m_width, m_height,
                },
                m_origin,
                m_rotation,
                m_color
            );

            DrawText(
                m_value.data(),
                m_position.x + 10, m_position.y + 10,
                m_height - 10,
                BLACK
            );
        }

    private:
        Vector2 m_origin;
        float m_width;
        float m_height;
    };
}
