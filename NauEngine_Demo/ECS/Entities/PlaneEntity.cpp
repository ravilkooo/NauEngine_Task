#include "PlaneEntity.h"

PlaneEntity::PlaneEntity(ID3D11Device* device) {
	auto& renderComp = this->AddComponent<RenderComponent>();

	renderComp.mesh = ResourceManager::Instance().Load<Mesh>("./Models/plane.obj", device, "./Models/plane.obj");
	renderComp.texture = ResourceManager::Instance().Load<Texture>("./Textures/plane_Diffuse.dds", device, "./Textures/plane_Diffuse.dds");
	renderComp.vertexShader = ResourceManager::Instance().Load<VertexShader>("./Shaders/Custom_VShader.hlsl", device, L"./Shaders/Custom_VShader.hlsl");
	renderComp.pixelShader = ResourceManager::Instance().Load<PixelShader>("./Shaders/Custom_PShader.hlsl", device, L"./Shaders/Custom_PShader.hlsl");

	auto& transformComp = this->AddComponent<TransformComponent>(device);
	// Too big mesh -> Resizing
	transformComp.SetScaleFactor(0.05f);

	// Align plane
	transformComp.SetLocalRotation({ 0, DirectX::XM_PIDIV2, 0 });

	// Setting initial position
	transformComp.SetWorldMatrix(Matrix::CreateTranslation({ 5,0,0 }));
}

void PlaneEntity::Tick(float deltaTime) {
	auto& transformComp = this->GetComponent<TransformComponent>();

	// Rotating object around Y-axis
	transformComp.TransformWorldMatrix(Matrix::CreateFromAxisAngle({ 0,1,0 }, deltaTime));

	// Local rotation
	transformComp.LocalRotate({ 4*deltaTime, 0, 0 });
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