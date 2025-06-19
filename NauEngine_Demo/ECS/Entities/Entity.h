#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <nlohmann_json/json.hpp>
#include <d3d11.h>

#include "ECS/Components/Component.h"

using json = nlohmann::json;

// class Component;

class Entity
{
public:
	// virtual ~Entity() = default;

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

    // Serialization
    virtual std::string getTypeName() const = 0;

    virtual void to_json(json& j) = 0;
    virtual void from_json(ID3D11Device* device, const json& j) = 0;
    

protected:
    std::vector<std::unique_ptr<Component>> components;
};

	// аналог SceneNode x Drawable ?
