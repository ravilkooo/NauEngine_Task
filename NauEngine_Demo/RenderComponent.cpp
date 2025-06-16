#include "RenderComponent.h"

void RenderComponent::Render(ID3D11DeviceContext* context)
{
	inputLayout->Bind(context);
	vertexShader->Bind(context);
	pixelShader->Bind(context);
	mesh->Draw(context);
}
