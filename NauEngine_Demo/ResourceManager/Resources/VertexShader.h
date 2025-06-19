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
    VertexShader() {};
    VertexShader(ID3D11Device* device, std::string filePath) : VertexShader(device, std::wstring(filePath.begin(), filePath.end()).c_str()) {};
    VertexShader(ID3D11Device* device, LPCWSTR filePath);
    ~VertexShader();
    void Bind(ID3D11DeviceContext* context); // noexcept ?
    ID3DBlob* GetBytecode() const noexcept;
    void Release();

    const std::string getTypeName() const override { return "VertexShader"; };

private:
    Microsoft::WRL::ComPtr<ID3DBlob> pShaderBytecodeBlob;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

