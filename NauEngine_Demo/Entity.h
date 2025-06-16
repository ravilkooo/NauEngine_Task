#pragma once

#include <vector>
#include <memory>
#include <iostream>

class Component;

class Entity
{
public:
	virtual ~Entity() = default;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *component;
        components.push_back(std::move(component));
        return ref;
    }

    template<typename T>
    bool hasComponent() const {
        for (auto& comp : components) {
            if (typeid(T) == comp->getType()) return true;
        }
        return false;
    }

    template<typename T>
    T& getComponent() {
        for (auto& comp : components) {
            if (typeid(T) == comp->getType()) {
                return *static_cast<T*>(comp.get());
            }
        }
        throw std::runtime_error("Component not found");
    }

protected:
    std::vector<std::unique_ptr<Component>> components;
};

	// аналог SceneNode x Drawable ?
