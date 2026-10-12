#include "Scene.h"

Scene::Scene(const std::string& name)
{
}

Scene::~Scene()
{
	CloseScene();
}


void Scene::Update(float fDeltaTime)
{
	for (Entity* entity : entities)
	{
		entity->Update(fDeltaTime);
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

void Scene::OpenScene() {
	for (Entity* entity : entities)
	{
		entity->Start();
	}
	
}

void Scene::CloseScene() {
	for (Entity* entity : entities)
	{
		entity->Destroy();
	}
	entities.clear();
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for (const Entity* entity : entities)
	{
		entity->Draw(window);
	}
}