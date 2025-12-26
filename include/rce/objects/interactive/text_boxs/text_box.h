#pragma once
#include "rce/objects/interactive/interactive_object.h"

namespace rce {
    class TextBox : public InteractiveObject {
    public:
        void onHover(const Vector2& mouseLocation, InteractiveObject*) override;
        [[nodiscard]] std::string getValue();

        [[nodiscard]] virtual bool isAllowed(char toCheck) { return true; }

        void setValue(const std::string& value);

    protected:
        int m_maxCharacters;
        std::string m_value{};
    };
}
