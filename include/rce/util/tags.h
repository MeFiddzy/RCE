#pragma once
#include <set>
#include <string>
#include "rce/objects/abstract_object.h"

namespace rce {
    constexpr inline const char* TAGS_PROPERTY_NAME = "_RCE:TAGS";

    class Tag {
    public:
        Tag(const std::string &name) {
            m_name = name;
        }

        [[nodiscard]] const std::string& getName() const {
            return m_name;
        }

        void addTo(AbstractObject* obj) const {
            if (!obj->hasProperty(TAGS_PROPERTY_NAME)) {
                obj->setProperty(TAGS_PROPERTY_NAME, std::set{*this});
            }
            else {
                auto tags = obj->getPropriety<std::set<Tag>>(TAGS_PROPERTY_NAME)->getValue();

                if (!tags.contains(*this))
                    tags.insert(*this);

                obj->setProperty(TAGS_PROPERTY_NAME, tags);
            }
        }

        void removeFrom(AbstractObject* obj) const {
            if (!obj->hasProperty(TAGS_PROPERTY_NAME))
                return;

            auto tags = obj->getPropriety<std::set<Tag>>(TAGS_PROPERTY_NAME)->getValue();

            if (!tags.contains(*this))
                return;

            tags.erase(*this);

            obj->setProperty(TAGS_PROPERTY_NAME, tags);
        }

        bool tagIn(AbstractObject* obj) const {
            if (!obj->hasProperty(TAGS_PROPERTY_NAME))
                return false;

            auto tags = obj->getPropriety<std::set<Tag>>(TAGS_PROPERTY_NAME)->getValue();

            if (!tags.contains(*this))
                return false;

            return true;
        }

        bool operator<(const Tag& obj) const {
            return m_name < obj.getName();
        }

        bool operator>(const Tag& obj) const {
            return m_name > obj.getName();
        }
    private:
        std::string m_name;
    };
}
