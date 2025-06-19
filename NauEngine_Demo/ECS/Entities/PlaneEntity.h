#pragma once
#include "Entity.h"

#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

#include "ResourceManager/ResourceManager.h"

#include "ResourceManager/Resources/VertexShader.h"
#include "ResourceManager/Resources/PixelShader.h"
#include "ResourceManager/Resources/Mesh.h"
#include "ResourceManager/Resources/TransformCBuffer.h"

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

