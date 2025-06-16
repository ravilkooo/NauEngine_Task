#pragma once
#include <typeinfo>

class Component
{
public:
    virtual ~Component() = default;

    virtual void Delete() = 0;

    virtual const std::type_info& getType() const = 0;

    Component& operator=(const Component&) = delete;
};
