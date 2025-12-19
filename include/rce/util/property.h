#pragma once

namespace rce {

    template<typename T>
    class Property;

    class PropertyBase {
    public:
        virtual ~PropertyBase() = default;

        template<typename T>
        Property<T>* castInto() {
            return dynamic_cast<Property<T>*>(this);
        }

        template<typename T>
        const Property<T>* castInto() const {
            return dynamic_cast<const Property<T>*>(this);
        }
    };

    template<typename T>
    class Property final : public PropertyBase {
    public:
        Property(const T& value) : m_value(value) {}

        const T& getValue() const {
            return m_value;
        }

        void setValue(const T& value) {
            m_value = value;
        }

        PropertyBase& toBase() {
            return *this;
        }

    private:
        T m_value{};
    };

}
