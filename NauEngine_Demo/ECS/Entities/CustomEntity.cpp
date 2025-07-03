#include "CustomEntity.h"

CustomEntity::CustomEntity(ID3D11Device* device, std::string meshFilePath, std::string textureFilePath, std::string scriptFilePath,
	Vector3 initPosition, Vector3 initScale, Vector3 initRotation)
{
	auto& renderComp = this->AddComponent<RenderComponent>();

	renderComp.mesh = ResourceManager::Instance().Load<Mesh>(meshFilePath, device, meshFilePath);
	renderComp.texture = ResourceManager::Instance().Load<Texture>(textureFilePath, device, textureFilePath);
	renderComp.vertexShader = ResourceManager::Instance().Load<VertexShader>("./Shaders/Custom_VShader.hlsl", device, L"./Shaders/Custom_VShader.hlsl");
	renderComp.pixelShader = ResourceManager::Instance().Load<PixelShader>("./Shaders/Custom_PShader.hlsl", device, L"./Shaders/Custom_PShader.hlsl");

	auto& transformComp = this->AddComponent<TransformComponent>(device);
	transformComp.SetWorldMatrix(Matrix::CreateTranslation(initPosition));
	transformComp.SetScaleFactor(initScale);
	transformComp.SetLocalRotation(initRotation);

	auto& scriptComp = this->AddComponent<LuaScriptComponent>();
	scriptComp.scriptFile = scriptFilePath;
}

CustomEntity::CustomEntity(ID3D11Device* device, std::string meshFilePath, std::string textureFilePath, std::string scriptFilePath) :
	CustomEntity(device, meshFilePath, textureFilePath, scriptFilePath, { 0.0f, 0.0f, 0.0f }, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f})
{
}

void CustomEntity::Tick(float deltaTime) {

}

std::string CustomEntity::getTypeName() const
{
	return "CustomEntity";
}

void CustomEntity::to_json(json& j)
{
	j["type"] = getTypeName();
	j["components"] = json::array();

	for (const auto& comp : components) {
		json comp_json;
		comp_json["type"] = comp->getTypeName();
		comp->to_json(comp_json["data"]);
		j["components"].push_back(comp_json);
	}

}

void CustomEntity::from_json(ID3D11Device* device, const json& j)
{
	assert(j["type"] == getTypeName());
	for (const auto& j_c : j["components"]) {
		std::string type = j_c.at("type").get<std::string>();
		std::unique_ptr<Component> component;
		if (type == "RenderComponent") {
			component = std::make_unique<RenderComponent>();
		}
		else if (type == "TransformComponent") {
			component = std::make_unique<TransformComponent>();
		}
		else if (type == "LuaScriptComponent") {
			component = std::make_unique<LuaScriptComponent>();
		}
		else {
			continue;
		}
		component->from_json(device, j_c["data"]);
		components.push_back(std::move(component));
	}
}