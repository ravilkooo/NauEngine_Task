#pragma once
#include <directxmath.h>
#include "ConstantBuffer.h"
#include "Resource.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class TransformComponent;


class TransformCBuffer
	 : public Resource
{
protected:
	struct Transforms
	{
		Matrix wMat;
		Matrix wMatInvTranspose;
	};
public:
	TransformCBuffer(ID3D11Device* device, TransformComponent* parent, UINT slot = 0u);
	void Bind(ID3D11DeviceContext* context) noexcept;

	// ~TransformCBuffer() override = default;

private:
	// static
	VertexConstantBuffer* pVcbuf;
	TransformComponent* pParent = nullptr;
};
