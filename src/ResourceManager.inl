#include "ResourceManager.h"
template <typename R, typename I>
void ResourceManager<R, I>::loadResource(I id, const std::string& filename)
{
    // Create and load resource
    std::unique_ptr<R> resource(new R());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceManager::load - Failed to load " + filename);

    // If loading successful, insert resource to map
    insertResource(id, std::move(resource));
}

template <typename R, typename I>
R& ResourceManager<R, I>::getResource(I id)
{
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());

    return *found->second;
}

template <typename R, typename I>
const R& ResourceManager<R, I>::getResource(I id) const
{
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());

    return *found->second;
}

template <typename R, typename I>
void ResourceManager<R, I>::insertResource(I id, std::unique_ptr<R> resource)
{
    // Insert and check success
    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}