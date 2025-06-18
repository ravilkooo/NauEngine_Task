#include "Scene.h"
#include <fstream>

Scene::Scene()
{
    json data;
    /*
    std::ofstream outfstream("scene_out.json");
    stuff_to_json(data, Json_stuff({4,1,4}));
    outfstream << std::setw(4) << data << std::endl;
    */
    std::ifstream f("scene_out.json");
    f >> data;
    Json_stuff t2;
    t2.from_json(data);
    std::cout << t2.x << " " << t2.y << " " << t2.z << "\n";
    // = data.get<Json_stuff>(); // גûחûגאוע from_json

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
