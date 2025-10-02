#pragma once

#include "memory"

namespace mefiddzy {
    class Object;

    class IObjectComponent {
    public:
        virtual void onTick(mefiddzy::Object &self) {}

        explicit IObjectComponent(Object &parent) : m_parent(parent) {}
        virtual ~IObjectComponent() = default;

        Object& getParent() {
            return m_parent;
        }

        static std::unique_ptr<IObjectComponent> createComponent() {
            return nullptr;
        };

    private:

        Object &m_parent;
    };
}