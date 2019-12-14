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
  for (auto& l_entity : entities)
    l_entity->Render();
}

Entity& EntityManager::AddEntity(std::string f_entityName)
{
  Entity* l_entity = new Entity(*this, f_entityName);
  entities.emplace_back(l_entity);
  return *l_entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
  return entities;
}

unsigned EntityManager::GetEntityCount()
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
