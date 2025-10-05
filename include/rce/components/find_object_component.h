#include <vector>
#include <unordered_map>
#include "rce/components/component.h"

namespace rce {
    class FindObjectIDComponent : public IObjectComponent {
    public:
        explicit FindObjectIDComponent(const std::string &id);

        void onAdd(rce::Object &parent) override;

        __forceinline std::string getId() {
            return m_id;
        }

        static Object* getObjectByID(const std::string &id);
    private:
        std::string m_id{};

        static std::unordered_map<std::string, Object*> s_ids;
    };
}