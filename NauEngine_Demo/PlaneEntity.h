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

class PlaneEntity :
    public Entity
{
public:
	PlaneEntity() = default;
	PlaneEntity(ID3D11Device* device);
	void Tick(float deltaTime) override;

	float accumTime;

	// Serialization
	std::string getTypeName() const override;

	void to_json(json& j) override;
	void from_json(ID3D11Device* device, const json& j) override;
};

