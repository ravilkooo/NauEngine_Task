#pragma once

#include "Entity.h"

#include "ResourceManager.h"

#include "RenderComponent.h"
#include "TransformComponent.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Mesh.h"
#include "MeshUtils.h"

#include "TransformCBuffer.h"

class SimpleEntity : public Entity
{
public:
	//TransformComponent& transfromComp;
	//RenderComponent& renderComp;

	SimpleEntity(ID3D11Device* device, int num);
	void Tick(float deltaTime) override;

	float accumTime;

	// Serialization
	std::string getTypeName() const override;

	void to_json(json& j) override;
	void from_json(const json& j) override;
};