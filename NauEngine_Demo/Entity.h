#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "Component.h"

// class Component;

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
    bool HasComponent() const {
        for (auto& comp : components) {
            if (typeid(T) == comp->getType()) return true;
        }
        return false;
    }

    template<typename T>
    T& GetComponent() {
        for (auto& comp : components) {
            if (typeid(T) == comp->getType()) {
                return *static_cast<T*>(comp.get());
            }
        }
        throw std::runtime_error("Component not found");
    }

    virtual void Tick(float deltaTime) = 0;

protected:
    std::vector<std::unique_ptr<Component>> components;
};

	// аналог SceneNode x Drawable ?
