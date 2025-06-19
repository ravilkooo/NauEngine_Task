#include "SimpleEntity.h"


SimpleEntity::SimpleEntity(ID3D11Device* device, int num) {
	auto& renderComp = this->AddComponent<RenderComponent>();

	//renderComp.mesh = CreateUnwrappedCubeMesh(device);
	renderComp.mesh = ResourceManager::Instance().Load<Mesh>("./Models/gamepad.obj", device, "./Models/gamepad.obj");

	renderComp.vertexShader = ResourceManager::Instance().Load<VertexShader>("./Shaders/Cube_VShader.hlsl", device, L"./Shaders/Cube_VShader.hlsl");
	renderComp.pixelShader = ResourceManager::Instance().Load<PixelShader>("./Shaders/Cube_PShader.hlsl", device, L"./Shaders/Cube_PShader.hlsl");

	auto& transformComp = this->AddComponent<TransformComponent>(device);
	transformComp.SetOffset({ 0, 0, num * 3.0f / 100 });
	transformComp.SetScaleFactor(num * 2.0f / 100);
}

void SimpleEntity::Tick(float deltaTime) {
	accumTime += deltaTime;
	auto& transformComp = this->GetComponent<TransformComponent>();
	transformComp.LocalRotate({ deltaTime * 2, 0, 0 });

	transformComp.SetOffset({ 4.0f * transformComp.scaleFactor.x * cos(transformComp.scaleFactor.x * accumTime),
		4.0f * transformComp.scaleFactor.x * sin(transformComp.scaleFactor.x * accumTime), 3});
}

std::string SimpleEntity::getTypeName() const
{
	return "SimpleEntity";
}

void SimpleEntity::to_json(json& j)
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

void SimpleEntity::from_json(ID3D11Device* device, const json& j)
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