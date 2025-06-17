#pragma once

#include <vector>
#include "Entity.h"

class Scene
{
public:
    Scene();
    ~Scene();

    // To-do smart ptr?
    void AddEntity(Entity* node);
    void RemoveEntity(Entity* node);
    void Tick(float deltaTime);
    void Draw();

    // To-do smart ptr?
    std::vector<Entity*> entities;
};

