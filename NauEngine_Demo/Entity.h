#pragma once

#include <vector>
#include <memory>

class Component;

class Entity
{
public:
	virtual ~Entity() = default;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template<typename T>
    bool hasComponent() const;

    template<typename T>
    T& getComponent();

protected:
    std::vector<std::unique_ptr<Component>> components;
};

	// аналог SceneNode x Drawable ?
