#pragma once
#include "Resource.h"

#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <stdexcept>

class PixelShader :
    public Resource
{
public:
    PixelShader(ID3D11Device* device, LPCWSTR filePath);
    void Bind(ID3D11DeviceContext* context);; //  noexcept;
private:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};

