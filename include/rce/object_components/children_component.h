#pragma once

#include "rce/objects/sprite_object.h"
#include "object_component.h"

namespace rce {
    class ChildrenComponent : public IObjectComponent {
    public:
        ChildrenComponent() = default;

        bool& followRotation();
        bool& followScale();
        std::pair<bool, bool>& followPosition();

        void onTick(rce::AbstractObject *parent) override;

        ChildrenComponent& addChild(std::shared_ptr<AbstractObject> &child);

    private:
        bool m_followRotation = false;
        bool m_followScale = false;
        std::pair<bool, bool> m_followPosition = {true, true};

        std::vector<std::weak_ptr<AbstractObject>> m_children;
    };
}