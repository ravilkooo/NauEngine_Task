#pragma once

#include "Resource.h"
#include <memory>
#include <vector>
#include <stdexcept>
#include <d3d11.h>
#include <wrl/client.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

struct Vertex
{
    Vector3 position;
    Vector3 normal;
    Vector2 texcoord;
};

class Mesh : public Resource
{
public:
    Mesh(ID3D11Device* device,
        const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices);

    void Draw(ID3D11DeviceContext* context) const;

    UINT GetIndexCount() const { return m_indexCount; }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
    UINT m_indexCount = 0;

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizer;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthState;
};

