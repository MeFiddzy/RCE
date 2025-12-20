#pragma once
#include <random>

#include "raylib.h"

namespace rce::examples::util {
    inline Color randomColor() {
        std::mt19937 rngEngine(std::random_device{}());
        std::uniform_int_distribution rngColor(0, 255);

        return Color(rngColor(rngEngine), rngColor(rngEngine), rngColor(rngEngine));
    }
}
