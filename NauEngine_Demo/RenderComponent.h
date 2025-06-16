#pragma once
#include "Component.h"
#include "Mesh.h"

// ������ Drawable ?
class RenderComponent :
    public Component
{
protected:
    ~RenderComponent() = default; // ���������� ���������� ? TO-DO: what is it ?

public:
    virtual void Render() = 0;

    // TO-DO ptr
    Mesh* nesh;

    // To-do: Material
};

