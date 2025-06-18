#include "RenderComponent.h"
#include "ResourceManager.h"

void RenderComponent::Render(ID3D11DeviceContext* context)
{
	vertexShader->Bind(context);
	pixelShader->Bind(context);
	if (texture) {
		texture->Bind(context);
	}
	mesh->Draw(context);
}

std::string RenderComponent::getTypeName() const
{
	return "RenderComponent";
}

void RenderComponent::to_json(json& j)
{
	j = json{
		{"mesh", mesh ? mesh->GetResourceKey() : ""},
		// {"inputLayout", inputLayout ? inputLayout->GetResourceKey() : ""},
		{"vertexShader", vertexShader ? vertexShader->GetResourceKey() : ""},
		{"pixelShader", pixelShader ? pixelShader->GetResourceKey() : ""}
	};
}

void RenderComponent::from_json(ID3D11Device* device, const json& j)
{
	mesh = ResourceManager::Instance().Load<Mesh>(j.at("mesh").get<std::string>(), device, j.at("mesh").get<std::string>());
 	vertexShader = ResourceManager::Instance().Load<VertexShader>(j.at("vertexShader").get<std::string>(), device, j.at("vertexShader").get<std::string>());
	pixelShader = ResourceManager::Instance().Load<PixelShader>(j.at("pixelShader").get<std::string>(), device, j.at("pixelShader").get<std::string>());
}
