#include "SimpleEntity.h"


SimpleEntity::SimpleEntity(ID3D11Device* device, int num) {
	auto& renderComp = this->AddComponent<RenderComponent>();

	//renderComp.mesh = CreateUnwrappedCubeMesh(device);
	renderComp.mesh = ResourceManager::Instance().Load<Mesh>("./Models/MissedMesh.obj", device, "./Models/MissedMesh.obj");

	renderComp.vertexShader = ResourceManager::Instance().Load<VertexShader>("./Shaders/Cube_VShader.hlsl", device, L"./Shaders/Cube_VShader.hlsl");
	renderComp.pixelShader = ResourceManager::Instance().Load<PixelShader>("./Shaders/Cube_PShader.hlsl", device, L"./Shaders/Cube_PShader.hlsl");

	auto& transformComp = this->AddComponent<TransformComponent>(device);

	// Different sizes for cubes
	transformComp.SetScaleFactor(num * 2.0f / 100);

	// Setting initial position
	transformComp.SetWorldMatrix(Matrix::CreateTranslation({ 4.0f * transformComp.scaleFactor.x, 0, num * 3.0f / 100 }));
}

void SimpleEntity::Tick(float deltaTime) {
	auto& transformComp = this->GetComponent<TransformComponent>();

	// Local rotation
	transformComp.LocalRotate({ deltaTime * 2, 0, 0 });

	// Rotating object around Z-axis
	transformComp.TransformWorldMatrix(Matrix::CreateFromAxisAngle({ 0,0,1 }, transformComp.scaleFactor.x * deltaTime));
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