#include <iostream>
#include "Entity.h"

Entity::Entity(EntityManager& f_manager) : m_manager(f_manager)
{
  m_isActive = true;
}

Entity::Entity(EntityManager& f_manager, std::string f_name) : m_name(f_name), m_manager(f_manager)
{
  m_isActive = true;
}

void Entity::Update(float f_deltaTime)
{
  for (auto& component : m_components)
    component->Update(f_deltaTime);
}

void Entity::Render()
{
  for (auto& component : m_components)
    component->Render();
}

void Entity::Destroy()
{
  m_isActive = false;
}

bool Entity::IsActive() const
{
  return m_isActive;
}

void Entity::ListAllComponents() const
{
  for (auto mapElement : m_componentTypeMap)
    std::cout << "  Component<" << mapElement.first->name() << ">" << std::endl;
}
