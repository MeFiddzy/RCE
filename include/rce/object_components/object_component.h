#pragma once

#include <memory>
#include "rce/objects/abstract_object.h"

namespace rce {
    class Object;

    class IObjectComponent {
    public:
        virtual void onTick(rce::AbstractObject* parent) {}

        virtual void onAdd(rce::AbstractObject* parent) {}

        IObjectComponent() = default;
        virtual ~IObjectComponent() = default;

        void enable();
        void disable();
        void toggle();
        [[nodiscard]] bool isEnabled() const;

    private:
        bool m_enabled = true;
    };
}