#pragma once

#include "Resources/Resource.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <unordered_map>
#include <nlohmann_json/json.hpp>
#include <d3d11.h>

using json = nlohmann::json;

class ResourceManager {
public:
    static ResourceManager& Instance() {
        static ResourceManager inst;
        return inst;
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> Load(const std::string& id, Args&&... args) {
        auto it = resources.find(id);
        if (it != resources.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        auto resource = std::make_shared<T>(std::forward<Args>(args)...);
        resources[id] = resource;
        resources[id]->resourceKey = id;
        return resource;
    }

    void Unload(const std::string& id) {
        resources.erase(id);
    }

    void to_json(json& j);
    void from_json(ID3D11Device* device, const json& j);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
};

