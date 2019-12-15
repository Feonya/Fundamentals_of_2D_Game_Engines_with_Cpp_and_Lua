#include <iostream>
#include "Entity.h"

Entity::Entity(EntityManager& f_manager) : manager(f_manager)
{
  isActive = true;
}

Entity::Entity(EntityManager& f_manager, std::string f_name, LayerType f_layer) : 
    name(f_name), layer(f_layer), manager(f_manager)
{
  isActive = true;
}

void Entity::Update(float f_deltaTime)
{
  for (auto& l_component : components)
    l_component->Update(f_deltaTime);
}

void Entity::Render()
{
  for (auto& l_component : components)
    l_component->Render();
}

void Entity::Destroy()
{
  isActive = false;
}

bool Entity::IsActive() const
{
  return isActive;
}

void Entity::ListAllComponents() const
{
  for (auto l_mapElement : componentTypeMap)
    std::cout << "  Component<" << l_mapElement.first->name() << ">" << std::endl;
}
