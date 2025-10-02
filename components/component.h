#pragma once

#include "memory"

namespace mefiddzy {
    class Object;

    class IObjectComponent {
    public:
        virtual void onTick(mefiddzy::Object &self) {}

        explicit IObjectComponent() {}
        virtual ~IObjectComponent() = default;

    private:
    };
}