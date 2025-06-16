#pragma once
#include "Component.h"

// ������ Drawable ?
class RenderComponent :
    public Component
{
protected:
    ~RenderComponent() = default; // ���������� ���������� ? TO-DO: what is it ?

public:
    virtual void Render(bool activate) = 0;
};

