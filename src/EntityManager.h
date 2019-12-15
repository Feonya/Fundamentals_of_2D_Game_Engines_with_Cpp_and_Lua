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
    Entity& AddEntity(std::string f_entityName, LayerType f_layer);
    std::vector<Entity*> GetEntities() const;
    std::vector<Entity*> GetEntitiesByLayer(LayerType f_layer) const;
    unsigned GetEntityCount() const;

    void ListAllEntities() const;

  private:
    std::vector<Entity*> entities;
};

#endif
