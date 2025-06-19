#include "TransformCBuffer.h"
#include "ECS/Components/TransformComponent.h"

#include <iostream>

TransformCBuffer::TransformCBuffer(ID3D11Device* device, TransformComponent* parent, UINT slot)
	: pParent(parent)
{
	//if (!pVcbuf)
	{
		pVcbuf = new VertexConstantBuffer(device, sizeof(Transforms), nullptr, slot);
	}
}

void TransformCBuffer::Bind(ID3D11DeviceContext* context) noexcept
{
	const auto wMat = pParent->GetFullTransform();
	Matrix A = wMat;
	// Correct ?
	A._41 = 0;
	A._42 = 0;
	A._43 = 0;
	A._44 = 1;
	//A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	// float det = A.Determinant();

	const auto wMatInvTranspose = (A.Invert()).Transpose();

	const Transforms tf = {
			wMat, wMatInvTranspose,
	};
	pVcbuf->Update(context, &tf);
	pVcbuf->Bind(context);
}
	
// VertexConstantBuffer* TransformCBuffer::pVcbuf  = nullptr;
