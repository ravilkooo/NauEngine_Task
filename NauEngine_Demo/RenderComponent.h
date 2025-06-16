#pragma once
#include "Component.h"

// аналог Drawable ?
class RenderComponent :
    public Component
{
protected:
    ~RenderComponent() = default; // защищенный деструктор ? TO-DO: what is it ?

public:
    virtual void Render(bool activate) = 0;
};

