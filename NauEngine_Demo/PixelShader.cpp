#include "PixelShader.h"
#include <iostream>

PixelShader::PixelShader(ID3D11Device* device, LPCWSTR filePath)
{
	Microsoft::WRL::ComPtr<ID3DBlob> pShaderBytecodeBlob;
	ID3DBlob* errorPixelCode;
	HRESULT hr = D3DCompileFromFile(
		filePath,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pShaderBytecodeBlob,
		&errorPixelCode);

	if (FAILED(hr)) {
		if (errorPixelCode) {
			char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());
			// throw std::runtime_error(compileErrors);
			std::cout << compileErrors << " - // -- " << std::endl;
		}
		else
		{
			std::cout << filePath << L" - Missing Shader File\n";
			/*
			char text[256];
			sprintf_s(text, 256 * sizeof(char), "%s - Missing Shader File\n", filePath);
			throw std::runtime_error(text);
			*/
		}

		return;
	}
	if (FAILED(hr)) return;

	hr = device->CreatePixelShader(
		pShaderBytecodeBlob->GetBufferPointer(),
		pShaderBytecodeBlob->GetBufferSize(),
		nullptr,
		&pPixelShader);
	pShaderBytecodeBlob->Release();
}

void PixelShader::Bind(ID3D11DeviceContext* context)
{
	context->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
