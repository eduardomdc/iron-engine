#ifndef component_manager_hpp
#define component_manager_hpp

#include <vector>
#include <cstdint>
#include <unordered_map>

using Entity = uint32_t;
const Entity INVALID_ENTITY = 0;

template<typename T>
class ComponentManager {
public:
    void add(Entity entity, const T& component) {
        if (entity_to_index.find(entity) != entity_to_index.end()) return;
        size_t index = components.size();
        entity_to_index[entity] = index;
        index_to_entity.push_back(entity);
        components.push_back(component);
    }
    T* get(Entity e) {
        auto it = entity_to_index.find(e);
        if (it == entity_to_index.end()) return nullptr;
        return &components[it->second];
    }
    void remove(Entity entity) {
        auto it = entity_to_index.find(entity);
        if (it == entity_to_index.end()) return;
        size_t index = it->second;
        size_t last = components.size() - 1;

        //compact list
        components[index] = components[last];
        index_to_entity[index] = index_to_entity[last];
        entity_to_index[index_to_entity[index]] = index;

        components.pop_back();
        index_to_entity.pop_back();
        entity_to_index.erase(entity);
    }

    std::vector<T>& all() {
        return components;
    }

    std::vector<Entity>& entities () {
        return index_to_entity;
    }

private:
    std::vector<T> components;
    std::vector<Entity> index_to_entity;
    std::unordered_map<Entity, size_t> entity_to_index;
};

#endif
