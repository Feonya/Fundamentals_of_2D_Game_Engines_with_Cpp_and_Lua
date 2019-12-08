#include "Entity.h"

Entity::Entity(EntityManager& manager) : manager_(manager), is_active_(true) {}

Entity::Entity(EntityManager& manager, std::string name) :
  Name(name), manager_(manager), is_active_(true) {}

void Entity::Update(float deltaTime)
{
  for (auto& component : components_)
    component->Update(deltaTime);
}

void Entity::Render()
{
  for (auto& component : components_)
    component->Render();
}

void Entity::Destroy()
{
  is_active_ = false;
}

bool Entity::IsActive() const
{
  return is_active_;
}
