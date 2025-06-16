#include "InputLayout.h"

InputLayout::InputLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* inputElements, UINT numInputElements, ID3DBlob* pShaderBytecodeBlob)
{
    device->CreateInputLayout(
        inputElements,
        numInputElements,
        pShaderBytecodeBlob->GetBufferPointer(),
        pShaderBytecodeBlob->GetBufferSize(),
        &pInputLayout);
}

void InputLayout::Bind(ID3D11DeviceContext* context)
{
    context->IASetInputLayout(pInputLayout.Get());
}
