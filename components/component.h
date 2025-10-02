#pragma once

#include "memory"

namespace mefiddzy {
    class Object;

    class IObjectComponent {
    public:
        virtual void onTick(mefiddzy::Object &self) {}

        IObjectComponent() = default;
        virtual ~IObjectComponent() = default;

    private:
    };
}