#pragma once
class Component
{
protected:
    virtual ~Component() = default;

public:
    virtual void Delete() = 0;

    Component& operator=(const Component&) = delete;
};
