#include "EntityManager.h"

void EntityManager::ClearData()
{
  for (auto& l_entity : m_entities)
    l_entity->Destroy();
}

bool EntityManager::HasNoEntities()
{
  return m_entities.size() == 0;
}

void EntityManager::Update(float f_deltaTime)
{
  for (auto& l_entity : m_entities)
    l_entity->Update(f_deltaTime);
}

void EntityManager::Render()
{
  for (auto& l_entity : m_entities)
    l_entity->Render();
}

Entity& EntityManager::AddEntity(std::string f_entityName)
{
  Entity* l_entity = new Entity(*this, f_entityName);
  m_entities.emplace_back(l_entity);
  return *l_entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
  return m_entities;
}

unsigned int EntityManager::GetEntityCount()
{
  return m_entities.size();
}
