#pragma once
#include <functional>

#include "../interactive_object.h"
#include "rce/objects/shape/rectangle_object.h"

namespace rce {
    class AbstractButton : public InteractiveObject {
    public:
        static void emptyFunc(const Vector2&, AbstractButton*) {}

        void onHover(const Vector2 &mouseLocation, InteractiveObject* obj) override { m_onHover(mouseLocation, dynamic_cast<AbstractButton*>(obj)); }

        void onClick(const Vector2 &mouseLocation, InteractiveObject* obj) override { m_onClick(mouseLocation, dynamic_cast<AbstractButton*>(obj)); }

        void onButtonDown(const Vector2 &mouseLocation, InteractiveObject* obj) override { m_onButtonDown(mouseLocation, dynamic_cast<AbstractButton*>(obj)); }

        void onRelease(const Vector2 &mouseLocation, InteractiveObject* obj) override { m_onRelease(mouseLocation, dynamic_cast<AbstractButton*>(obj)); }
    protected:
        std::function<void(const Vector2 &, AbstractButton*)> m_onHover;
        std::function<void(const Vector2 &, AbstractButton*)> m_onClick;
        std::function<void(const Vector2 &, AbstractButton*)> m_onButtonDown;
        std::function<void(const Vector2 &, AbstractButton*)> m_onRelease;
    };
}