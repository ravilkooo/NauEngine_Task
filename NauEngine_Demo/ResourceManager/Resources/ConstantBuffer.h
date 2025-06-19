#pragma once
#include "Resource.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <SimpleMath.h>
#include <iostream>

class ConstantBuffer
	: public Resource
{
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	UINT slot;
	size_t dataSize;

public:
	virtual void Update(ID3D11DeviceContext* context, const void* consts) {
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		context->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
		memcpy(mappedResource.pData, consts, dataSize + (16 - (dataSize % 16))); // aligned size
		context->Unmap(pConstantBuffer.Get(), 0);
		//context->VSSetConstantBuffers(0u, 1u, &pConstantBuffer);
	}

	ConstantBuffer(ID3D11Device* device, size_t dataSize, const void* consts = nullptr, UINT slot = 0u)
		:
		slot(slot), dataSize(dataSize)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = dataSize + (16 - (dataSize % 16));  // aligned size
		cbd.StructureByteStride = 0u;

		if (consts)
		{
			D3D11_SUBRESOURCE_DATA InitData = {};
			InitData.pSysMem = consts;
			HRESULT hr = device->CreateBuffer(&cbd, &InitData, &pConstantBuffer);
			if (FAILED(hr))
				std::cout << "FAIL!\n";
		}
		else
		{
			HRESULT hr = device->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
			if (FAILED(hr))
				std::cout << "FAIL!\n";
		}
	}
	
	// ~ConstantBuffer() override = default;

	const std::string getTypeName() const override { return "ConstantBuffer"; };
};

class VertexConstantBuffer : public ConstantBuffer
{
	using ConstantBuffer::pConstantBuffer;
	using ConstantBuffer::slot;
public:
	using ConstantBuffer::ConstantBuffer;
	void Bind(ID3D11DeviceContext* context) noexcept
	{
		context->VSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
	}

	// ~VertexConstantBuffer() override = default;

	const std::string getTypeName() const override { return "VertexConstantBuffer"; };
};

class PixelConstantBuffer : public ConstantBuffer
{
	using ConstantBuffer::pConstantBuffer;
	using ConstantBuffer::slot;
public:
	using ConstantBuffer::ConstantBuffer;
	void Bind(ID3D11DeviceContext* context) noexcept
	{
		context->PSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
	}

	// ~PixelConstantBuffer() override = default;

	const std::string getTypeName() const override { return "PixelConstantBuffer"; };
};


class ComputeConstantBuffer : public ConstantBuffer
{
	using ConstantBuffer::pConstantBuffer;
	using ConstantBuffer::slot;
public:
	using ConstantBuffer::ConstantBuffer;
	void Bind(ID3D11DeviceContext* context) noexcept
	{
		context->CSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
	}

	// ~ComputeConstantBuffer() override = default;

	const std::string getTypeName() const override { return "ComputeConstantBuffer"; };
};
/*
*/
