#include "EntityManager.h"

void EntityManager::ClearData()
{
  for (auto& entity : m_entities)
    entity->Destroy();
}

bool EntityManager::HasNoEntities()
{
  return m_entities.size() == 0;
}

void EntityManager::Update(float f_deltaTime)
{
  for (auto& entity : m_entities)
    entity->Update(f_deltaTime);
}

void EntityManager::Render()
{
  for (auto& entity : m_entities)
    entity->Render();
}

Entity& EntityManager::AddEntity(std::string f_entityName)
{
  Entity* entity = new Entity(*this, f_entityName);
  m_entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
  return m_entities;
}

unsigned int EntityManager::GetEntityCount()
{
  return m_entities.size();
}
