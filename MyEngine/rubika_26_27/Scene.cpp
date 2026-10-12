#include "Scene.h"

Scene::Scene(const std::string& name)
{
}

Scene::~Scene()
{
	for (Entity* entity : entities)
	{
		entity->Destroy();
	}
	entities.clear();
}

void Scene::Start()
{
	for (Entity* entity : entities)
	{
		entity->Start();
	}
}

void Scene::Update(float fDeltaTime)
{
	for (Entity* entity : entities)
	{
		entity->Update(fDeltaTime);
	}
}

void Scene::Destroy()
{
	for (Entity* entity : entities)
	{
		entity->Destroy();
	}
}

void Scene::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void Scene::RemoveEntity(Entity* entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for (const Entity* entity : entities)
	{
		entity->Draw(window);
	}
}