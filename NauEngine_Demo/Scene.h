#pragma once

#include "ECS/Entities/Entity.h"
#include "ECS/Entities/Camera.h"

#include <vector>
#include <nlohmann_json/json.hpp>

using json = nlohmann::json;

class Scene
{
public:
    Scene();
    ~Scene() = default;

    void AddEntity(std::unique_ptr<Entity> entity);
    void RemoveEntity(std::unique_ptr<Entity> entity);
    void Tick(float deltaTime);
    // void Draw();
    
    void Clear();
    std::vector <std::unique_ptr<Entity>> entities;

    std::shared_ptr<Camera> mainCamera;

    // Serialization
    void to_json(json& j);
    void from_json(ID3D11Device* device, const json& j);
};

