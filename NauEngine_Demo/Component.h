#pragma once
#include <typeinfo>
#include <string>
#include <nlohmann_json/json.hpp>
#include <d3d11.h>

using json = nlohmann::json;

class Component
{
public:
    virtual ~Component() = default;

    virtual const std::type_info& getType() const = 0;

    // Serialization
    virtual std::string getTypeName() const = 0;

    virtual void to_json(json& j) = 0;
    virtual void from_json(ID3D11Device* device, const json& j) = 0;
};
