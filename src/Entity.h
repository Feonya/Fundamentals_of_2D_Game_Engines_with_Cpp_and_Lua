#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity {
  public:
    std::string m_name;

    Entity(EntityManager& f_manager);
    Entity(EntityManager& f_manager, std::string f_name);

    void Update(float f_deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    template<typename T, typename... TArgs>
    T& AddComponent(TArgs&&... f_args)
    {
      T* newComponent(new T(std::forward<TArgs>(f_args)...));
      newComponent->m_owner = this;
      m_components.emplace_back(newComponent);
      m_componentTypeMap[&typeid(*newComponent)] = newComponent;
      newComponent->Initialize();
      return *newComponent;
    }

    template<typename T>
    T* GetComponent()
    {
      return static_cast<T*>(m_componentTypeMap[&typeid(T)]);
    }

  private:
    EntityManager& m_manager;
    bool m_isActive;
    std::vector<Component*> m_components;
    std::map<const std::type_info*, Component*> m_componentTypeMap;
};

#endif
