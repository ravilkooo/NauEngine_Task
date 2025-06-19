#include "Texture.h"

#include <iostream>

Texture::Texture(ID3D11Device* device, const std::string& filePath)
	: filePath(filePath)
{
	D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT{});
	auto hr = device->CreateSamplerState(&samplerDesc, &pSampler);
	if (FAILED(hr)) {
		// std::cout << "FAILED Sample create\n";
	}

	if (StringHelper::GetFileExtension(filePath) == "dds")
	{
		//std::cout << "DDS loaded!!! " << filePath << " :: " << StringHelper::GetFileExtension(filePath) << "\n";
		HRESULT hr = DirectX::CreateDDSTextureFromFile(device,
			StringHelper::StringToWide(filePath).c_str(), &pTexture, &pTextureView);
		if (FAILED(hr))
		{
			this->Initialize1x1ColorTexture(device, SE_Colors::UnloadedTextureColor);
		}
		return;
	}
	else
	{
		// std::cout << "Wrong texture file extension: " << StringHelper::GetFileExtension(filePath) << "\n";
		this->Initialize1x1ColorTexture(device, SE_Colors::UnloadedTextureColor);

	}
}

void Texture::Bind(ID3D11DeviceContext* context) noexcept
{
	context->PSSetSamplers(0u, 1u, pSampler.GetAddressOf());
	context->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}

void Texture::Initialize1x1ColorTexture(ID3D11Device* device, const SE_Color& colorData)
{
	InitializeColorTexture(device, &colorData, 1, 1);
}

void Texture::InitializeColorTexture(ID3D11Device* device, const SE_Color* colorData, UINT width, UINT height)
{

	CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);

	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = colorData;
	initialData.SysMemPitch = width * sizeof(SE_Color);

	ID3D11Texture2D* p2DTexture = nullptr;
	HRESULT hr = device->CreateTexture2D(&textureDesc, &initialData, &p2DTexture);
	if (FAILED(hr)) {
		throw std::runtime_error("Failed to initialize texture from color data.");
	}

	pTexture = static_cast<ID3D11Texture2D*>(p2DTexture);

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);

	hr = device->CreateShaderResourceView(pTexture.Get(), &srvDesc, &pTextureView);
	if (FAILED(hr)) {
		throw std::runtime_error("Failed to create shader resource view from texture generated from color data.");
	}
}

const std::string Texture::getTypeName() const
{
	return "Texture";
}

SE_Color::SE_Color()
	:color(0)
{
}

SE_Color::SE_Color(unsigned int val)
	: color(val)
{
}

SE_Color::SE_Color(BYTE r, BYTE g, BYTE b)
	: SE_Color(r, g, b, 255)
{
}

SE_Color::SE_Color(BYTE r, BYTE g, BYTE b, BYTE a)
{
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

SE_Color::SE_Color(const SE_Color& src)
	:color(src.color)
{
}

SE_Color& SE_Color::operator=(const SE_Color& src)
{
	this->color = src.color;
	return *this;
}

bool SE_Color::operator==(const SE_Color& rhs) const
{
	return (this->color == rhs.color);
}

bool SE_Color::operator!=(const SE_Color& rhs) const
{
	return !(*this == rhs);
}

constexpr BYTE SE_Color::GetR() const
{
	return this->rgba[0];
}
void SE_Color::SetR(BYTE r)
{
	this->rgba[0] = r;
}

constexpr BYTE SE_Color::GetG() const
{
	return this->rgba[1];
}
void SE_Color::SetG(BYTE g)
{
	this->rgba[1] = g;
}

constexpr BYTE SE_Color::GetB() const
{
	return this->rgba[2];
}
void SE_Color::SetB(BYTE b)
{
	this->rgba[2] = b;
}

constexpr BYTE SE_Color::GetA() const
{
	return this->rgba[3];
}
void SE_Color::SetA(BYTE a)
{
	this->rgba[3] = a;
}