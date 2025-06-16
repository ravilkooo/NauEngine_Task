#pragma once
#include "Component.h"

#include <wrl.h>
#include <d3d11.h>
#include <directxmath.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class TransformComponent :
    public Component
{
protected:
    ~TransformComponent() = default; // защищенный деструктор ? TO-DO: what is it ?

    void Delete() override {};

public:
    virtual void Transform() = 0;
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scale;    
};

