#pragma once

#include <memory>
#include <d3d11.h>
class Mesh;

std::shared_ptr<Mesh> CreateUnwrappedCubeMesh(ID3D11Device* device);

