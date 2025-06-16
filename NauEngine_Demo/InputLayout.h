#pragma once
#include "Resource.h"

#include <d3d11.h>
#include <wrl.h>

class InputLayout :
    public Resource
{
public:
    InputLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* inputElements, UINT numInputElements, ID3DBlob* pShaderBytecodeBlob);
    void Bind(ID3D11DeviceContext* context); // noexcept;

private:
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

