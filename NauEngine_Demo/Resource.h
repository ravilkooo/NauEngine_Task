#pragma once

#include <string>

class ResourceManager;

class Resource
{
    friend class ResourceManager;
private:
    std::string resourceKey;

public:
    virtual ~Resource() = default;
    virtual const std::string getTypeName() const = 0;
    const std::string& GetResourceKey() { return resourceKey; }

    // TO-DO:
    // template method Args... for Binding resource to pipeline
};

