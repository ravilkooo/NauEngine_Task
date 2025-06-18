#include "ResourceManager.h"
#include <fstream>

#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"

void ResourceManager::to_json(json& j)
{
    for (const auto& [key, resource] : resources) {
        json resJson;
        resJson["type"] = resource->getTypeName();
        resJson["key"] = resource->GetResourceKey();
        j["resources"].push_back(resJson);
    }
    std::ofstream("resources.json") << std::setw(4) << j;
}

void ResourceManager::from_json(ID3D11Device* device, const json& j)
{
    for (const auto& resJson : j["resources"]) {
        std::string type = resJson["type"];
        std::string key = resJson["key"];
        // auto params = resJson["params"];

        if (type == "VertexShader") {
            Load<VertexShader>(key, device, key);
        }
        else if (type == "PixelShader") {
            Load<VertexShader>(key, device, key);
        }
        else if (type == "Mesh") {
            Load<Mesh>(key, device, key);
        }
        else {
            continue;
        }

    }
}
