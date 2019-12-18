#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "components/ColliderComponent.h"

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
  //for (auto& l_entity : entities)
  //  l_entity->Update(f_deltaTime);

  //DestroyInactiveEntities();

  for (auto l_it = entities.begin(); l_it != entities.end(); ++l_it)
  {
    if ((*l_it)->IsActive()) (*l_it)->Update(f_deltaTime);
    else                     entities.erase(l_it);

  }
}

//void EntityManager::DestroyInactiveEntities()
//{
//  for (size_t l_i = 0; l_i < entities.size(); ++l_i)
//  {
//    if (!entities[l_i]->IsActive())
//      entities.erase(entities.begin() + l_i);
//  }
//}

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
      if (l_entity->layer == f_layer) l_selectedEntities.emplace_back(l_entity);

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

//std::string EntityManager::CheckEntityCollisions(Entity& f_myEntity) const
//{
//  ColliderComponent* l_myCollider = f_myEntity.GetComponent<ColliderComponent>();
//  for (auto& l_entity : entities)
//  {
//    if (l_entity->name.compare(f_myEntity.name) != 0 && l_entity->name.compare("tile") != 0)
//    {
//      if (l_entity->HasComponent<ColliderComponent>())
//      {
//        ColliderComponent* l_otherCollider = l_entity->GetComponent<ColliderComponent>();
//        if (Collision::CheckRectangleCollision(l_myCollider->collider, l_otherCollider->collider))
//            return l_otherCollider->colliderTag;
//      }
//    }
//  }
//
//  return std::string();
//}

CollisionType EntityManager::CheckCollisions() const
{
  for (auto& l_thisEntity : entities)
  {
    if (l_thisEntity->HasComponent<ColliderComponent>())
    {
      ColliderComponent* l_thisCollider = l_thisEntity->GetComponent<ColliderComponent>();
      for (auto& l_thatEntity : entities)
      {
        if (l_thatEntity->HasComponent<ColliderComponent>() &&
            l_thatEntity->name.compare(l_thisEntity->name) != 0)
        {
          ColliderComponent* l_thatCollider = l_thatEntity->GetComponent<ColliderComponent>();
          if (Collision::CheckRectangleCollision(l_thisCollider->collider,
              l_thatCollider->collider))
          {
            if (l_thisCollider->colliderTag.compare("player") == 0 &&
                l_thatCollider->colliderTag.compare("enemy") == 0)
              return PLAYER_ENEMY_COLLISION;
 
            if (l_thisCollider->colliderTag.compare("player") == 0 &&
                l_thatCollider->colliderTag.compare("projectile") == 0)
              return PLAYER_PROJECTILE_COLLISION;

            if (l_thisCollider->colliderTag.compare("enemy") == 0 &&
                l_thatCollider->colliderTag.compare("projectile") == 0)
              return ENEMY_PROJECTILE_COLLISION;

            if (l_thisCollider->colliderTag.compare("player") == 0 &&
                l_thatCollider->colliderTag.compare("vegetation") == 0)
              return PLAYER_VEGETATION_COLLISION;

            if (l_thisCollider->colliderTag.compare("player") == 0 &&
                l_thatCollider->colliderTag.compare("level_complete") == 0)
              return PLAYER_LEVEL_COMPLETE_COLLISION;
          }
        }
      }
    }
  }

  return NO_COLLISION;
}
