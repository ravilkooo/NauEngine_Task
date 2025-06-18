#include "Scene.h"

Scene::Scene()
{
    /*
    json data;
    std::ofstream outfstream("scene_out.json");
    stuff_to_json(data, Json_stuff({4,1,4}));
    outfstream << std::setw(4) << data << std::endl;
    */
    /*
    json data;
    std::ifstream f("scene_out.json");
    f >> data;
    Json_stuff t2;
    t2.from_json(data);
    std::cout << t2.x << " " << t2.y << " " << t2.z << "\n";
    // = data.get<Json_stuff>(); // вызывает from_json
    */

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

void Scene::to_json(json& j)
{
    json j_entities = json::array();
    for (const auto& e : entities) {
        json j_e;
        e->to_json(j_e);
        j_entities.push_back(j_e);
    }
    j["entities"] = j_entities;
}

void Scene::from_json(const json& j)
{
    for (const auto& j_e : j["entities"]) {
        std::string type = j_e.at("type").get<std::string>();
        /*
        std::unique_ptr<Entity> entity;
        if (type == "Player") {
            entity = std::make_unique<Player>();
        }
        else if (type == "Enemy") {
            entity = std::make_unique<Enemy>();
        } // ... другие типы
        entity->from_json(j_e);
        scene.entities.push_back(std::move(entity));
        */
    }

}
