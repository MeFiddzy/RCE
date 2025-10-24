#pragma once

#include <memory>

namespace rce {
    class Object;

    class IObjectComponent {
    public:
        virtual void onTick(rce::Object &parent) {}

        virtual void onAdd(rce::Object &parent) {}

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