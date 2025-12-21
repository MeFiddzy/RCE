#include "../shape/rectangle_object.h"
#include "raylib.h"

using namespace rce;

void RectangleObject::draw() {
    DrawRectanglePro(
        Rectangle {
            m_position.x, m_position.y,
            m_width, m_height,
        },
        m_origin,
        m_rotation,
        m_color
    );
}
