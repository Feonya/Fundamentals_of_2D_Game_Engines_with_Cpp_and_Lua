#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "constants.h"
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity {
  public:
    std::string name;
    LayerType   layer;

    Entity(EntityManager& f_manager);
    Entity(EntityManager& f_manager, std::string f_name, LayerType f_layer);

    void Update(float f_deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    template<typename T, typename... TArgs>
    T& AddComponent(TArgs&&... f_args)
    {
      T* l_newComponent(new T(std::forward<TArgs>(f_args)...));
      l_newComponent->owner = this;
      components.emplace_back(l_newComponent);
      componentTypeMap[&typeid(*l_newComponent)] = l_newComponent;
      l_newComponent->Initialize();
      return *l_newComponent;
    }

    template<typename T>
    T* GetComponent()
    {
      return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }

    template<typename T>
    bool HasComponent() const
    {
      return componentTypeMap.count(&typeid(T));
    }

    void ListAllComponents() const;

  private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*>                     components;
    std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif
