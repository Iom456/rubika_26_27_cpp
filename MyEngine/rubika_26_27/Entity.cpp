#include "Entity.h"

Entity::Entity(std::string friendlyName) : Transform(*this)
{
	Name = friendlyName;
}

Entity::~Entity()
{
	Destroy();
}

void Entity::Start()
{
	Transform.Start();
}

void Entity::Update(float fDeltaTime)
{
	//Transform.Update(fDeltaTime);
}

void Entity::Destroy()
{
	Transform.Destroy();
}

void Entity::Draw(sf::RenderWindow& window) const
{
	//chepo trop trop
}


