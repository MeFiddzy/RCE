#include <vector>
#include <unordered_map>
#include "rce/object_components/object_component.h"
#include "string"

namespace rce {
    class FindObjectIDComponent : public IObjectComponent {
    public:
        explicit FindObjectIDComponent(const std::string &id);

        void onAdd(rce::AbstractObject *parent) override;

        __forceinline std::string getId() {
            return m_id;
        }

        static AbstractObject* getObjectByID(const std::string &id);
    private:
        std::string m_id{};

        static std::unordered_map<std::string, AbstractObject*> s_ids;
    };
}