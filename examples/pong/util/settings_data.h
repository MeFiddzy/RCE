#pragma once
#include <cstdint>

#include "raylib.h"

namespace rce::examples {
    struct SettingsData {
        Vector2 p1Size, p2Size;
        Vector2 p1Movement, p2Movement;
        bool p1InvertedControls, p2InvertedControls;
        int winScore;
    };
}
