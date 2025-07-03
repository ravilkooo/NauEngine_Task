#pragma once

#include <d3d11.h>

#include "Component.h"

class LuaScriptComponent :
    public Component
{
public:
    std::string scriptFile;

    ~LuaScriptComponent() = default;

    const std::type_info& getType() const override {
        return typeid(LuaScriptComponent);
    }

    // Serialization
    std::string getTypeName() const override;

    void to_json(json& j) override;
    void from_json(ID3D11Device* device, const json& j) override;
};
