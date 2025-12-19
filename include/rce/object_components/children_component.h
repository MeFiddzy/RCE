#pragma once

#include "rce/objects/sprite_object.h"
#include "object_component.h"

namespace rce {
    class ChildrenComponent : public IObjectComponent {
    public:

        template <typename... Args,
                typename = std::enable_if_t<(std::conjunction_v<std::is_same<Args, std::weak_ptr<SpriteObject>>...>)>>
        explicit ChildrenComponent(Args ...children) {
            ((m_children.push_back(children)), ...);
        }
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