#pragma once

#include "StringHelper.h"
#include "Resource.h"

#include <wrl.h>
#include <d3d11.h>
#include <assimp/material.h>
#include <DDSTextureLoader.h>

class SE_Color;

class Texture :
	public Resource
{
public:	
	Texture(ID3D11Device* device, const std::string& filePath);
	void Bind(ID3D11DeviceContext* context) noexcept;
private:
	void Initialize1x1ColorTexture(ID3D11Device* device, const SE_Color& colorData);
	void InitializeColorTexture(ID3D11Device* device, const SE_Color* colorData, UINT width, UINT height);

	std::string filePath;
	Microsoft::WRL::ComPtr<ID3D11Resource> pTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;

	const std::string getTypeName() const override;

};

// ------------------------------

typedef unsigned char BYTE; // 8 bits

class SE_Color
{
public:
	SE_Color();
	SE_Color(unsigned int val);
	SE_Color(BYTE r, BYTE g, BYTE b);
	SE_Color(BYTE r, BYTE g, BYTE b, BYTE a);
	SE_Color(const SE_Color& src);

	SE_Color& operator=(const SE_Color& src);
	bool operator==(const SE_Color& rhs) const;
	bool operator!=(const SE_Color& rhs) const;

	constexpr BYTE GetR() const;
	void SetR(BYTE r);

	constexpr BYTE GetG() const;
	void SetG(BYTE g);

	constexpr BYTE GetB() const;
	void SetB(BYTE b);

	constexpr BYTE GetA() const;
	void SetA(BYTE a);

private:
	union
	{
		BYTE rgba[4];
		unsigned int color;
	};
};

namespace SE_Colors
{
	const SE_Color UnloadedTextureColor(100, 100, 100);
	const SE_Color UnhandledTextureColor(250, 0, 0);
}
