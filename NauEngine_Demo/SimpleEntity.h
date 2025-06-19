#pragma once

#include "Entity.h"

#include "ResourceManager.h"

#include "RenderComponent.h"
#include "TransformComponent.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Mesh.h"

#include "TransformCBuffer.h"

class SimpleEntity : public Entity
{
public:
	SimpleEntity() = default;
	SimpleEntity(ID3D11Device* device, int num);
	void Tick(float deltaTime) override;

	float accumTime;

	// Serialization
	std::string getTypeName() const override;

	void to_json(json& j) override;
	void from_json(ID3D11Device* device, const json& j) override;
};