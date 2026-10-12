#include "Scene.h"

Scene::Scene(const std::string& name)
{
	Name = name;
}

Scene::~Scene()
{
	CloseScene();
}


void Scene::Update(float fDeltaTime)
{
	for (Entity* entity : Entities)
	{
		entity->Update(fDeltaTime);
	}
}


void Scene::AddEntity(std::string name)
{
	Entities.push_back(new Entity(name));
}

void Scene::RemoveEntity(Entity* entity)
{
	Entities.erase(std::remove(Entities.begin(), Entities.end(), entity), Entities.end());
}

void Scene::OpenScene() {
	for (Entity* entity : Entities)
	{
		entity->Start();
	}
	
}

void Scene::CloseScene() {
	for (Entity* entity : Entities)
	{
		entity->Destroy();
	}
	Entities.clear();
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for (const Entity* entity : Entities)
	{
		entity->Draw(window);
	}
}