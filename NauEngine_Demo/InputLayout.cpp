#include "InputLayout.h"

InputLayout::InputLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* inputElements, UINT numInputElements, ID3DBlob* pShaderBytecodeBlob)
{
    /*UINT numInputElements = 3;
	D3D11_INPUT_ELEMENT_DESC* IALayoutInputElements = (D3D11_INPUT_ELEMENT_DESC*)malloc(numInputElements * sizeof(D3D11_INPUT_ELEMENT_DESC));

	IALayoutInputElements[0] =
		D3D11_INPUT_ELEMENT_DESC{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };
	IALayoutInputElements[1] =
		D3D11_INPUT_ELEMENT_DESC{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };
	IALayoutInputElements[2] =
		D3D11_INPUT_ELEMENT_DESC{
			"TEXCOORD",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };
	*/

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
