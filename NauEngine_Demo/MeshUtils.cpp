#include "MeshUtils.h"
#include "Mesh.h"

#include "ResourceManager.h"

#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
std::shared_ptr<Mesh> LoadModel(const std::string& path, UINT attrFlags)
{
    Assimp::Importer importer;
    const aiScene* pModel = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_FlipUVs
        | (((attrFlags & ModelLoader::VertexAttrFlags::NORMAL) != 0) ? aiProcess_GenNormals : 0x0)
    );

    //	aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    // aiProcess_GenNormals | aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded

    if (!pModel || pModel->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pModel->mRootNode)
    {
        rootNode = nullptr;
        return;
    }

    unsigned int meshesNum = 1; // pModel->mNumMeshes;

    size_t verticesNum = 0;
    size_t indicesNum = 0;

    verticesNum += pModel->mMeshes[0]->mNumVertices;
    indicesNum += pModel->mMeshes[0]->mNumFaces * 3;

    std::vector<Vertex> vertices = (CommonVertex*)calloc(rootNode->verticesNum, sizeof(CommonVertex));
    std::vector<uint32_t> indices = (int*)calloc(rootNode->indicesNum, sizeof(int));

    size_t vertexIdx = 0;
    size_t indexIdx = 0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(0, 1);

    const auto pMesh = pModel->mMeshes[0];

    //std::cout << (((attrFlags & ModelLoader::VertexAttrFlags::NORMAL))) << "\n";
    //std::cout << (((attrFlags & ModelLoader::VertexAttrFlags::NORMAL) != 0) ? aiProcess_GenNormals : 0x0) << "\n";
    for (unsigned i = 0; i < pMesh->mNumVertices; i++)
    {
        (rootNode->vertices)[vertexIdx++] = {
            XMFLOAT3(
            pMesh->mVertices[i].x,
            pMesh->mVertices[i].y,
            pMesh->mVertices[i].z
            ) };

        if (pMesh->mTextureCoords[0] && (attrFlags & VertexAttrFlags::TEXTURE))
        {
            //std::cout << "aiModel has texture!\n";
            (rootNode->vertices)[vertexIdx - 1].texCoord.x = (float)pMesh->mTextureCoords[0][i].x;
            (rootNode->vertices)[vertexIdx - 1].texCoord.y = (float)pMesh->mTextureCoords[0][i].y;
            //std::cout << (float)pMesh->mTextureCoords[0][i].x << ", " << (float)pMesh->mTextureCoords[0][i].y << "\n";
        }

        if (attrFlags & VertexAttrFlags::NORMAL) {
            (rootNode->vertices)[vertexIdx - 1].normal = {
                XMFLOAT3(
                pMesh->mNormals[i].x,
                pMesh->mNormals[i].y,
                pMesh->mNormals[i].z
                ) };
        }
    }
    for (unsigned i = 0; i < pMesh->mNumFaces; i++)
    {
        aiFace face = pMesh->mFaces[i];
        assert(face.mNumIndices == 3);

        auto col = XMFLOAT4(distr(gen), distr(gen), distr(gen), 1);

        for (unsigned j = 0; j < face.mNumIndices; j++) {
            (rootNode->indices)[indexIdx++] = face.mIndices[j];

            (rootNode->vertices)[face.mIndices[j]].color = col;

        }
    }
    
    //if (pMesh->mTextureCoords[0] && (attrFlags & VertexAttrFlags::TEXTURE))
    //{
    //    aiMaterial* material = pModel->mMaterials[pMesh->mMaterialIndex];
    //    std::vector<Texture> diffuseTextures = rootNode->LoadMaterialTextures(material, aiTextureType::aiTextureType_DIFFUSE, pModel);
    //    rootNode->textures.insert(rootNode->textures.end(), diffuseTextures.begin(), diffuseTextures.end());
    //}
    
    return;
}
*/

std::shared_ptr<Mesh> CreateUnwrappedCubeMesh(ID3D11Device* device)
{
    // Развёртка "крестом" (UV-карта 3x4 квадрата, каждая грань в своём прямоугольнике)
    // Текстурные координаты (U, V) для каждой из 6 граней
    // Порядок граней: +X, -X, +Y, -Y, +Z, -Z

    // Размер одного квадрата на UV-карте
    const float du = 1.0f / 4.0f;
    const float dv = 1.0f / 3.0f;

    // Координаты центров квадратов для каждой грани (u0, v0)
    struct FaceUV {
        float u0, v0;
    };
    // Крест:       (см. ASCII ниже)
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

    // Вершины (позиция, нормаль, UV) для каждой грани
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    // Вспомогательные данные для каждой грани
    struct Face {
        Vector3 normal;
        Vector3 v0, v1, v2, v3; // 4 вершины (по часовой стрелке)
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

    // Для каждой грани создаём 4 вершины с уникальными UV
    for (int f = 0; f < 6; ++f)
    {
        auto uv = faceUVs[f];
        // 4 угла квадрата в UV (по часовой стрелке)
        float u[4] = { uv.u0,           uv.u0 + du,     uv.u0 + du,     uv.u0 };
        float v[4] = { uv.v0 + dv,      uv.v0 + dv,     uv.v0,          uv.v0 };

        // 4 вершины
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
        // Индексы двух треугольников для этой грани
        int base = f * 4;
        indices.push_back(base + 0);
        indices.push_back(base + 2);
        indices.push_back(base + 1);
        indices.push_back(base + 0);
        indices.push_back(base + 3);
        indices.push_back(base + 2);
    }

    //return std::make_shared<Mesh>(device, vertices, indices);
    return ResourceManager::Instance().Load<Mesh>("CubeMesh", device, vertices, indices);
}