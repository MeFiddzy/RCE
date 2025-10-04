#pragma once

#include "memory"

namespace mefiddzy {
    class Object;

    class IObjectComponent {
    public:
        virtual void onTick(mefiddzy::Object &parent) {}

        IObjectComponent() = default;
        virtual ~IObjectComponent() = default;

    private:
    };
}