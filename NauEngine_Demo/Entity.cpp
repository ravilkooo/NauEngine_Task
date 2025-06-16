#include "Entity.h"

template<typename T, typename... Args>
T& Entity::AddComponent(Args&&... args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T& ref = *component;
    components.push_back(std::move(component));
    return ref;
}

template<typename T>
bool Entity::hasComponent() const {
    for (auto& comp : components) {
        if (typeid(T) == comp->getType()) return true;
    }
    return false;
}

template<typename T>
T& Entity::getComponent() {
    for (auto& comp : components) {
        if (typeid(T) == comp->getType()) {
            return *static_cast<T*>(comp.get());
        }
    }
    throw std::runtime_error("Component not found");
}
