#include "SimpleEntity.h"


SimpleEntity::SimpleEntity(ID3D11Device* device, int num) {
	auto& renderComp = this->AddComponent<RenderComponent>();

	renderComp.mesh = CreateUnwrappedCubeMesh(device);
	renderComp.vertexShader = new VertexShader(device, L"./Shaders/Cube_VShader.hlsl");
	renderComp.pixelShader = new PixelShader(device, L"./Shaders/Cube_PShader.hlsl");

	UINT numInputElements = 3;
	D3D11_INPUT_ELEMENT_DESC* IALayoutInputElements = (D3D11_INPUT_ELEMENT_DESC*)malloc(numInputElements * sizeof(D3D11_INPUT_ELEMENT_DESC));

	IALayoutInputElements[0] =
		D3D11_INPUT_ELEMENT_DESC{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };
	IALayoutInputElements[1] =
		D3D11_INPUT_ELEMENT_DESC{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };
	IALayoutInputElements[2] =
		D3D11_INPUT_ELEMENT_DESC{
			"TEXCOORD",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };

	renderComp.inputLayout = new InputLayout(device, IALayoutInputElements, 3, renderComp.vertexShader->GetBytecode());

	auto& transformComp = this->AddComponent<TransformComponent>(device);
	transformComp.SetPosition({ 0, 0, num * 3.0f / 100 });
	transformComp.SetScale(num * 2.0f / 100);
}

void SimpleEntity::Tick(float deltaTime) {
	accumTime += deltaTime;
	auto& transformComp = this->GetComponent<TransformComponent>();
	transformComp.Rotate({ deltaTime * 2, 0, 0 });

	transformComp.SetPosition({ 4.0f * transformComp.scaleFactor.x * cos(transformComp.scaleFactor.x * accumTime),
		4.0f * transformComp.scaleFactor.x * sin(transformComp.scaleFactor.x * accumTime), 3});
}