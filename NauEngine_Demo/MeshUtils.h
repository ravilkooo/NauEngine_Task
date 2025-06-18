#pragma once

#include <memory>
#include <d3d11.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

class Mesh;

enum VertexAttributesFlags : UINT {
    POSITION = 0x1,
    COLOR = 0x2,
    UV = 0x4,
    NORMAL = 0x8,
};

std::shared_ptr<Mesh> LoadModel(ID3D11Device* device, const std::string& path,
    UINT attrFlags = VertexAttributesFlags::POSITION);

std::shared_ptr<Mesh> CreateUnwrappedCubeMesh(ID3D11Device* device);
