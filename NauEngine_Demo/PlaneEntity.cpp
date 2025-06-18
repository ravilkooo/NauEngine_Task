#include "PlaneEntity.h"

PlaneEntity::PlaneEntity(ID3D11Device* device) {
	auto& renderComp = this->AddComponent<RenderComponent>();

	renderComp.mesh = ResourceManager::Instance().Load<Mesh>("./Models/plane.obj", device, "./Models/plane.obj");

	renderComp.vertexShader = ResourceManager::Instance().Load<VertexShader>("./Shaders/Cube_VShader.hlsl", device, L"./Shaders/Cube_VShader.hlsl");
	renderComp.pixelShader = ResourceManager::Instance().Load<PixelShader>("./Shaders/Cube_PShader.hlsl", device, L"./Shaders/Cube_PShader.hlsl");

	auto& transformComp = this->AddComponent<TransformComponent>(device);
	transformComp.SetOffset({ 4, 0, 0 });
}

void PlaneEntity::Tick(float deltaTime) {
	accumTime += deltaTime;
	auto& transformComp = this->GetComponent<TransformComponent>();

	transformComp.SetLocalRotation({ 0, -accumTime - DirectX::XM_PIDIV2, 0 });
	transformComp.SetOffset({ 4.0f * cos(accumTime), 0,
		4.0f * sin(accumTime) });
}

std::string PlaneEntity::getTypeName() const
{
	return "PlaneEntity";
}

void PlaneEntity::to_json(json& j)
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

void PlaneEntity::from_json(ID3D11Device* device, const json& j)
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
		else {
			continue;
		}
		component->from_json(device, j_c["data"]);
		components.push_back(std::move(component));
	}
}