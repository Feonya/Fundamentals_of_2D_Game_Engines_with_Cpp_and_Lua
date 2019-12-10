#include "Entity.h"

Entity::Entity(EntityManager& f_manager) : m_manager(f_manager), m_isActive(true) {}

Entity::Entity(EntityManager& f_manager, std::string f_name) :
  name(f_name), m_manager(f_manager), m_isActive(true) {}

void Entity::Update(float f_deltaTime)
{
  for (auto& l_component : m_components)
    l_component->Update(f_deltaTime);
}

void Entity::Render()
{
  for (auto& l_component : m_components)
    l_component->Render();
}

void Entity::Destroy()
{
  m_isActive = false;
}

bool Entity::IsActive() const
{
  return m_isActive;
}
