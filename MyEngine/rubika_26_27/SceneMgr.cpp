#include "SceneMgr.h"
#include "Logger.h"

SceneMgr::SceneMgr()
	: activeScene(nullptr)
{

}

void SceneMgr::Start()
{
	if (activeScene != nullptr)
	{
		activeScene->OpenScene();
	}
}

void SceneMgr::Update(float fDeltaTime) {
		if (activeScene){
			activeScene->Update(fDeltaTime);
		}
}

void SceneMgr::Destroy()
{
	for (auto scene : scenes) {
		scene.second->CloseScene();
	}
	scenes.clear();
}

void SceneMgr::AddScene(std::string& name) {
	if (!IsNameValid(name)) {
		Scene newScene = Scene(name);
		scenes[&name] = &newScene;
		Logger::Info("New Scene added to the map");
	}
}

void SceneMgr::RemoveScene(std::string& name) {
	if (IsNameValid(name)) {
		auto pair = scenes.find(&name);
		scenes.erase(pair);
		Logger::Info("A scene have been deleted");
	}
}

void SceneMgr::SetActiveScene(std::string& name) {
	if (!IsNameValid(name)) {
		Logger::Warning("The wanted scene does not exist impossible to change the active scene.");
		return;
	}

	if (activeScene == nullptr) {
		activeScene = scenes[&name];
		activeScene->OpenScene();
	}
	else{
		activeScene->CloseScene();
		activeScene = scenes[&name];
		activeScene->OpenScene();
	}

	Logger::Info("Active Scene changed");
}

bool SceneMgr::IsNameValid(std::string& name) {
	if (!scenes.contains(&name)) {
		Logger::Warning("A Scene with this name already exist");
		return false;
	}

	return true;
}


