#pragma once
#include "rce/objects/abstract_object.h"

namespace rce {
    class InteractiveObject : public AbstractObject {
    public:
        InteractiveObject() = default;

        virtual void onHover(const Vector2& mouseLocation, InteractiveObject*) {}
        virtual void onClick(const Vector2& mouseLocation, InteractiveObject*) {}
        virtual void onRelease(const Vector2& mouseLocation, InteractiveObject*) {}
        virtual void onButtonDown(const Vector2& mouseLocation, InteractiveObject*) {}

        [[nodiscard]] const Rectangle& getTriggerShape() const {
            return m_triggerShape;
        }

    protected:
        Rectangle m_triggerShape{};
    };
}
