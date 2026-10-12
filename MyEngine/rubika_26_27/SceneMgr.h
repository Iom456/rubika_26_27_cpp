#pragma once

#include "Scene.h"
#include <map>

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	void Start();
	void Update(float fDeltaTime);
	void Destroy();

	void AddScene(std::string& name);
	void RemoveScene(std::string& name);

	void SetActiveScene(std::string& name);
	bool IsNameValid(std::string& name);
	Scene* GetActiveScene() const { return activeScene; }

private:
	std::map<std::string*, Scene*> scenes;
	Scene* activeScene;
}; 

