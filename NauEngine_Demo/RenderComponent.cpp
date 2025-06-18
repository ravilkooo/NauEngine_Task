#include "RenderComponent.h"

void RenderComponent::Render(ID3D11DeviceContext* context)
{
	inputLayout->Bind(context);
	vertexShader->Bind(context);
	pixelShader->Bind(context);
	mesh->Draw(context);
}

std::string RenderComponent::getTypeName() const
{
	return "RenderComponent";
}

void RenderComponent::to_json(json& j)
{
	j = json{
		{ "mesh", "rc_mesh" }
		/*
		{"mesh", mesh ? mesh->GetResourceKey() : ""},
		{"inputLayout", inputLayout ? inputLayout->GetResourceKey() : ""},
		{"vertexShader", vertexShader ? vertexShader->GetResourceKey() : ""},
		{"pixelShader", pixelShader ? pixelShader->GetResourceKey() : ""}
		*/
	};
}

void RenderComponent::from_json(const json& j)
{
}
