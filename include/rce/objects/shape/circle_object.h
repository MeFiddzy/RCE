#pragma once
#include "../abstract_object.h"

namespace rce {
    class CircleObject : public AbstractObject {
    public:
        CircleObject(Vector2 position, Color color, float radius) : m_radius(radius) {
            m_position = position;
            m_color = color;
        }

        void draw() override;

        void setRadius(float radius);

        float getRadius() const;
    private:
        float m_radius;
    };
}
