#pragma once

#include <string>
#include "Entity.h"
#include <vector>

namespace sf
{
	class RenderWindow;
}

class Scene
{
public:

	Scene(const std::string& name);
	~Scene();

	virtual void OpenScene();
	virtual void Update(float fDeltaTime);
	virtual void CloseScene();

	void AddEntity(std::string name);
	void RemoveEntity(Entity* entity);

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
	std::string Name;
	std::vector<Entity*> Entities;
	
};