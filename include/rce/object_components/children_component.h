#pragma once

#include "rce/objects/object.h"
#include "object_component.h"

namespace rce {
    class ChildrenComponent : public IObjectComponent {
    public:

        template <typename... Args,
                typename = std::enable_if_t<(std::conjunction_v<std::is_same<Args, std::weak_ptr<Object>>...>)>>
        explicit ChildrenComponent(Args ...children) {
            ((m_children.push_back(children)), ...);
        }
        ChildrenComponent() = default;

        bool& followRotation();
        bool& followScale();
        std::pair<bool, bool>& followPosition();

        void onTick(rce::Object &parent) override;

        ChildrenComponent& addChild(std::shared_ptr<Object> &child);

    private:
        bool m_followRotation = false;
        bool m_followScale = false;
        std::pair<bool, bool> m_followPosition = {true, true};

        std::vector<std::weak_ptr<Object>> m_children;
    };
}