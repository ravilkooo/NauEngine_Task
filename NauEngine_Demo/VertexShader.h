#pragma once
#include "Resource.h"

#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <stdexcept>

class VertexShader :
    public Resource
{
public:
    VertexShader(ID3D11Device* device, LPCWSTR filePath);
    void Bind(ID3D11DeviceContext* context); // noexcept ?
    ID3DBlob* GetBytecode() const noexcept;

private:
    Microsoft::WRL::ComPtr<ID3DBlob> pShaderBytecodeBlob;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};

