#pragma once
#include "Component.h"
class TransformComponent :
    public Component
{
protected:
    ~TransformComponent() = default; // защищенный деструктор ? TO-DO: what is it ?

public:
    virtual void Transform(bool activate) = 0;
};

