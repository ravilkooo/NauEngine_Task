#pragma once
#include "Component.h"
class TransformComponent :
    public Component
{
protected:
    ~TransformComponent() = default; // ���������� ���������� ? TO-DO: what is it ?

public:
    virtual void Transform(bool activate) = 0;
};

