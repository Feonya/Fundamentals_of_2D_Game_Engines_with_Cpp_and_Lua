#include "EntityManager.h"

void EntityManager::ClearData()
{
  for (auto& entity : entities_)
    entity->Destroy();
}

bool EntityManager::HasNoEntities()
{
  return entities_.size() == 0;
}

void EntityManager::Update(float deltaTime)
{
  for (auto& entity : entities_)
    entity->Update(deltaTime);
}

void EntityManager::Render()
{
  for (auto& entity : entities_)
    entity->Render();
}

Entity& EntityManager::AddEntity(std::string entityName)
{
  Entity* entity = new Entity(*this, entityName);
  entities_.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
  return entities_;
}

unsigned int EntityManager::GetEntityCount()
{
  return entities_.size();
}
