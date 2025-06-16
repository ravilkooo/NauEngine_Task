#include "MeshUtils.h"
#include "Mesh.h"

#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


std::shared_ptr<Mesh> CreateUnwrappedCubeMesh(ID3D11Device* device)
{
    // �������� "�������" (UV-����� 3x4 ��������, ������ ����� � ���� ��������������)
    // ���������� ���������� (U, V) ��� ������ �� 6 ������
    // ������� ������: +X, -X, +Y, -Y, +Z, -Z

    // ������ ������ �������� �� UV-�����
    const float du = 1.0f / 4.0f;
    const float dv = 1.0f / 3.0f;

    // ���������� ������� ��������� ��� ������ ����� (u0, v0)
    struct FaceUV {
        float u0, v0;
    };
    // �����:       (��. ASCII ����)
    //        +Y
    //   -X  +Z  +X  -Z
    //        -Y
    FaceUV faceUVs[6] = {
        {2 * du, 1 * dv}, // +X
        {0 * du, 1 * dv}, // -X
        {1 * du, 0 * dv}, // +Y
        {1 * du, 2 * dv}, // -Y
        {1 * du, 1 * dv}, // +Z
        {3 * du, 1 * dv}  // -Z
    };

    // ������� (�������, �������, UV) ��� ������ �����
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    // ��������������� ������ ��� ������ �����
    struct Face {
        Vector3 normal;
        Vector3 v0, v1, v2, v3; // 4 ������� (�� ������� �������)
        int faceIndex;
    };

    Face faces[] = {
        // +X
        { { 1, 0, 0 }, { 0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f,  0.5f }, { 0.5f,  0.5f,  0.5f }, { 0.5f,  0.5f, -0.5f }, 0 },
        // -X
        { {-1, 0, 0 }, {-0.5f, -0.5f,  0.5f }, {-0.5f, -0.5f, -0.5f }, {-0.5f,  0.5f, -0.5f }, {-0.5f,  0.5f,  0.5f }, 1 },
        // +Y
        { { 0, 1, 0 }, {-0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f,  0.5f }, {-0.5f,  0.5f,  0.5f }, 2 },
        // -Y
        { { 0,-1, 0 }, {-0.5f, -0.5f,  0.5f }, { 0.5f, -0.5f,  0.5f }, { 0.5f, -0.5f, -0.5f }, {-0.5f, -0.5f, -0.5f }, 3 },
        // +Z
        { { 0, 0, 1 }, { 0.5f, -0.5f,  0.5f }, {-0.5f, -0.5f,  0.5f }, {-0.5f,  0.5f,  0.5f }, { 0.5f,  0.5f,  0.5f }, 4 },
        // -Z
        { { 0, 0,-1 }, {-0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, {-0.5f,  0.5f, -0.5f }, 5 }
    };

    // ��� ������ ����� ������ 4 ������� � ����������� UV
    for (int f = 0; f < 6; ++f)
    {
        auto uv = faceUVs[f];
        // 4 ���� �������� � UV (�� ������� �������)
        float u[4] = { uv.u0,           uv.u0 + du,     uv.u0 + du,     uv.u0 };
        float v[4] = { uv.v0 + dv,      uv.v0 + dv,     uv.v0,          uv.v0 };

        // 4 �������
        XMFLOAT3 pos[4] = { faces[f].v0, faces[f].v1, faces[f].v2, faces[f].v3 };
        for (int i = 0; i < 4; ++i)
        {
            Vertex vert;
            vert.position.x = pos[i].x;
            vert.position.y = pos[i].y;
            vert.position.z = pos[i].z;
            vert.normal.x = faces[f].normal.x;
            vert.normal.y = faces[f].normal.y;
            vert.normal.z = faces[f].normal.z;
            vert.texcoord.x = u[i];
            vert.texcoord.y = v[i];
            vertices.push_back(vert);
        }
        // ������� ���� ������������� ��� ���� �����
        int base = f * 4;
        indices.push_back(base + 0);
        indices.push_back(base + 1);
        indices.push_back(base + 2);
        indices.push_back(base + 0);
        indices.push_back(base + 2);
        indices.push_back(base + 3);
    }

    return std::make_shared<Mesh>(device, vertices, indices);
}
