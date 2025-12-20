#include "circle_object.h"

using namespace rce;

void CircleObject::draw() {
    DrawCircle(m_position.x, m_position.y, m_radius, m_color);
}

void CircleObject::setRadius(float radius) {
    m_radius = radius;
}

float CircleObject::getRadius() const {
    return m_radius;
}
