#include <iostream>
#include "EntityManager.h"

void EntityManager::ClearData()
{
  for (auto& l_entity : entities)
    l_entity->Destroy();
}

bool EntityManager::HasNoEntities()
{
  return entities.size() == 0;
}

void EntityManager::Update(float f_deltaTime)
{
  for (auto& l_entity : entities)
    l_entity->Update(f_deltaTime);
}

void EntityManager::Render()
{
  for (unsigned l_layerNumber = 0; l_layerNumber < NUM_LAYERS; ++l_layerNumber)
    for (auto& l_entity : GetEntitiesByLayer(static_cast<LayerType>(l_layerNumber)))
    {
      l_entity->Render();
    }
}

Entity& EntityManager::AddEntity(std::string f_entityName, LayerType f_layer)
{
  Entity* l_entity = new Entity(*this, f_entityName, f_layer);
  entities.emplace_back(l_entity);
  return *l_entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
  return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType f_layer) const
{
    std::vector<Entity*> l_selectedEntities;
    for (auto& l_entity : entities)
      if (l_entity->layer == f_layer)
        l_selectedEntities.emplace_back(l_entity);

    return l_selectedEntities;
}

unsigned EntityManager::GetEntityCount() const
{
  return entities.size();
}

void EntityManager::ListAllEntities() const
{
  unsigned l_i = 0;
  for (auto& l_entity : entities)
  {
    std::cout << "Entity[" << l_i << "]: " << l_entity->name << std::endl;
    l_entity->ListAllComponents();
    ++l_i;
  }
}
