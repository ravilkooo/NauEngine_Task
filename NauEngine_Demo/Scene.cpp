#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (auto entity : entities)
    {
        delete entity;
    }
}

void Scene::AddEntity(Entity* entity)
{
    entities.push_back(entity);
}

void Scene::RemoveEntity(Entity* entity)
{
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void Scene::Tick(float deltaTime)
{
    for (auto entity : entities)
    {
        entity->Tick(deltaTime);
    }
}

void Scene::Draw()
{
    for (auto entity : entities)
    {
        //entity->Draw();
    }
}
