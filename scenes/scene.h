#pragma once

#include <vector>
#include <memory>

namespace mefiddzy {
    class Object;
    namespace scenes {
        class IScene {
        public:
            virtual ~IScene() = default;

            virtual void gameLoop() {}

            virtual std::vector<std::unique_ptr<Object>> getObjectsForLoad() {
                return {};
            }

        protected:
            std::vector<Object> m_objects;
        };

    }
}