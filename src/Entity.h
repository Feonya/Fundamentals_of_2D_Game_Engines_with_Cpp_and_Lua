#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity {
  public:
    std::string Name;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    template<typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args)
    {
      T* newComponent(new T(std::forward<TArgs>(args)...));
      newComponent->Owner = this;
      components_.emplace_back(newComponent);
      newComponent->Initialize();

      return *newComponent;
    }

  private:
    EntityManager& manager_;
    std::vector<Component*> components_;
    bool is_active_;
};

#endif
