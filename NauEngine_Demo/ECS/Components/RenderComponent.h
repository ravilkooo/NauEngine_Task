#pragma once

#include <d3d11.h>

#include "Component.h"

#include "ResourceManager/Resources/Mesh.h"
#include "ResourceManager/Resources/VertexShader.h"
#include "ResourceManager/Resources/PixelShader.h"
#include "ResourceManager/Resources/Texture.h"

class RenderComponent :
    public Component
{
public:
    ~RenderComponent() = default; 

    void Render(ID3D11DeviceContext* context);

    const std::type_info& getType() const override {
        return typeid(RenderComponent);
    }

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<VertexShader> vertexShader;
    std::shared_ptr<PixelShader> pixelShader;

    // Serialization
    std::string getTypeName() const override;

    void to_json(json& j) override;
    void from_json(ID3D11Device* device, const json& j) override;
};

