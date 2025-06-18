#pragma once

#include <vector>
#include "Entity.h"
#include <nlohmann_json/json.hpp>

using json = nlohmann::json;

class Scene
{
public:
    Scene();
    ~Scene();

    class Json_stuff {
    public:
        Json_stuff() {};
        float x = 0, y = 0, z = 0;

        void to_json(json& j) {
            j = json{ {"x", this->x}, {"y", this->y}, {"z", this->z} };
        }
        void from_json(const json& j) {
            j.at("x").get_to(this->x);
            j.at("y").get_to(this->y);
            j.at("z").get_to(this->z);
        }
    };

    // To-do smart ptr?
    void AddEntity(Entity* node);
    void RemoveEntity(Entity* node);
    void Tick(float deltaTime);
    void Draw();

    // To-do smart ptr?
    std::vector<Entity*> entities;

    // Serialization
    
};

