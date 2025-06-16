#pragma once
#include "Component.h"
#include "Mesh.h"

// аналог Drawable ?
class RenderComponent :
    public Component
{
protected:
    ~RenderComponent() = default; // защищенный деструктор ? TO-DO: what is it ?

public:
    virtual void Render() = 0;

    // TO-DO ptr
    Mesh* nesh;

    // To-do: Material
};

