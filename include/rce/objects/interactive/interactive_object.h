#pragma once
#include "rce/objects/abstract_object.h"

namespace rce {
    struct InteractiveObject : public AbstractObject {
        InteractiveObject();

        virtual void onHover(Vector2 mouseLocation);
        virtual void onClick(Vector2 mouseLocation);
    };
}
