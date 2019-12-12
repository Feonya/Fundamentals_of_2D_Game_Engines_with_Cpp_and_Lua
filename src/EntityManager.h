#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "Entity.h"
#include "Component.h"

class EntityManager {
  public:
    void ClearData();
    void Update(float f_deltaTime);
    void Render();
    bool HasNoEntities();
    Entity& AddEntity(std::string f_entityName);
    std::vector<Entity*> GetEntities() const;
    unsigned GetEntityCount();

    void ListAllEntities() const;

  private:
    std::vector<Entity*> m_entities;
};

#endif
