#pragma once

#include <d3d11.h>

#include "Component.h"
#include "Mesh.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"

// аналог Drawable ?
class RenderComponent :
    public Component
{
public:
    ~RenderComponent() = default; // защищенный деструктор ? TO-DO: what is it ?

    // void Delete() override {};

    void Render(ID3D11DeviceContext* context);

    const std::type_info& getType() const override {
        return typeid(RenderComponent);
    }

    // TO-DO ptr
    std::shared_ptr<Mesh> mesh;
    InputLayout* inputLayout;
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    // To-do: Material
};

