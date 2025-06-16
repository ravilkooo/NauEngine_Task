#pragma once

#include "Entity.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"

class SimpleEntity : public Entity
{
public:
	SimpleEntity(ID3D11Device* device);
};