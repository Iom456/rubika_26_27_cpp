#pragma once

#include "Scene.h"
#include <map>

#include "DebugMgr.h"

class SceneMgr : public IDebugable
{
public:
	SceneMgr();
	~SceneMgr();

	void Initialize();
	void Shut();
	void DrawDebug() override;
	
	void Update(float fDeltaTime);

	void AddScene(std::string name);
	void RemoveScene(std::string name);

	void SetActiveScene(std::string name);
	bool IsSceneExist(std::string& name) const;
	Scene* GetActiveScene() const { return activeScene; }

private:
	std::map<std::string, Scene*> scenes;
	Scene* activeScene;
}; 

