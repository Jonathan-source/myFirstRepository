#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
/*
=====================================================================
The resource-class is made in such a manner that it can´t be copied.
It contains a function to load a resource, and another to get it.
Because of the RAII idiom, the choice has been made
to use the std::unique_ptr template class.
=====================================================================
*/
template<typename R, typename I = int>
class ResourceManager {
public:
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator =(ResourceManager& other) = delete;
    ResourceManager() = default;
    ~ResourceManager() = default;

    void loadResource(I id, const std::string& filename);
    R& getResource(I id);
    const R& getResource(I id) const;
private:
    void insertResource(I id, std::unique_ptr<R> resource);
    std::map<I, std::unique_ptr<R>> resourceMap;
};

#include "ResourceManager.inl"

