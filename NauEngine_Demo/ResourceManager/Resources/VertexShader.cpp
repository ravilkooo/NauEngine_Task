#include "VertexShader.h"

#include <iostream>

VertexShader::VertexShader(ID3D11Device* device, LPCWSTR filePath)
{
	std::cout << filePath << "\n";
	ID3DBlob* errorVertexCode = nullptr;
	HRESULT hr = D3DCompileFromFile(
		filePath,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pShaderBytecodeBlob,
		&errorVertexCode);

	if (FAILED(hr)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());
			//throw std::runtime_error(compileErrors);
			std::cout << compileErrors << " - // -- " << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			/*
			char text[256];
			sprintf_s(text, 256 * sizeof(char), "%s - Missing Shader File\n", filePath);
			throw std::runtime_error(text);
			*/
			std::cout << filePath << L" - Missing Shader File\n";
		}

	}

	device->CreateVertexShader(
		pShaderBytecodeBlob->GetBufferPointer(),
		pShaderBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	);

	UINT numInputElements = 4;
	D3D11_INPUT_ELEMENT_DESC* IALayoutInputElements =
		(D3D11_INPUT_ELEMENT_DESC*)malloc(numInputElements * sizeof(D3D11_INPUT_ELEMENT_DESC));

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
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
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
	IALayoutInputElements[3] =
		D3D11_INPUT_ELEMENT_DESC{
			"NORMAL",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };

	device->CreateInputLayout(
		IALayoutInputElements,
		numInputElements,
		pShaderBytecodeBlob->GetBufferPointer(),
		pShaderBytecodeBlob->GetBufferSize(),
		&pInputLayout);
}

void VertexShader::Bind(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(pInputLayout.Get());
	context->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pShaderBytecodeBlob.Get();
}
