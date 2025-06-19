#include "Scene.h"

#include "ECS/Entities/SimpleEntity.h"
#include "ECS/Entities/PlaneEntity.h"
#include "ECS/Entities/CustomEntity.h"

Scene::Scene()
{

}

void Scene::AddEntity(std::unique_ptr<Entity> entity)
{
    entities.push_back(std::move(entity));
}

void Scene::RemoveEntity(std::unique_ptr<Entity> entity)
{
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void Scene::Tick(float deltaTime)
{
    for (const auto& entity : entities)
    {
        entity->Tick(deltaTime);
    }
}

void Scene::to_json(json& j)
{
    json j_entities = json::array();
    for (const auto& e : entities) {
        json j_e;
        e->to_json(j_e);
        j_entities.push_back(j_e);
    }
    j["entities"] = j_entities;

    json j_c; mainCamera->to_json(j_c);
    j["camera"] = j_c;
}

void Scene::from_json(ID3D11Device* device, const json& j)
{
    for (const auto& j_e : j["entities"]) {
        std::string type = j_e.at("type").get<std::string>();
        std::unique_ptr<Entity> entity;
        if (type == "SimpleEntity") {
            entity = std::make_unique<SimpleEntity>();
        }
        else if (type == "PlaneEntity") {
            entity = std::make_unique<PlaneEntity>();
        }
        else if (type == "CustomEntity") {
            entity = std::make_unique<CustomEntity>();
        }
        else {
            continue;
        }
        entity->from_json(device, j_e);
        entities.push_back(std::move(entity));
    }
    mainCamera = std::make_shared<Camera>();
    mainCamera->from_json(device, j["camera"]);
}