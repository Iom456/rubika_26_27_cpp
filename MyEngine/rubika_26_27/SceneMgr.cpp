#include "SceneMgr.h"

#include "Globals.h"
#include "Logger.h"
#include "ImGui/imgui.h"

SceneMgr::SceneMgr()
	: activeScene(nullptr)
{

}

SceneMgr::~SceneMgr()
{
	Shut();
}

void SceneMgr::Initialize()
{
	if (activeScene != nullptr)
	{
		activeScene->OpenScene();
	}
	
	gData.DebugMgr->RegisterDebugableWindow("Scene", this);
}



void SceneMgr::Update(float fDeltaTime) {
		if (activeScene){
			activeScene->Update(fDeltaTime);
		}
}
void SceneMgr::Shut()
{
	for (auto scene : scenes)
	{
		scene.second->CloseScene();
	}
	scenes.clear();
	gData.DebugMgr->UnregisterDebugableWindow("Scene");
}

void SceneMgr::DrawDebug()
{
#ifdef _USE_IMGUI
	ImGui::Text("Scene active : %s",activeScene? activeScene->Name.c_str() : "aucune" );
	ImGui::Separator();
	
	for (auto& [name, scene] : scenes)
	{
		ImGui::PushID(name.c_str());
		
		if (ImGui::TreeNode(name.c_str()))
		{
			for (const auto& entity : scene->Entities)
			{
				ImGui::BulletText("%s", entity->Name.c_str());
			}
			
			if (ImGui::Button("Activer"))
			{
				SetActiveScene(name);
			}
			ImGui::SameLine();
			if (ImGui::Button("Ajouter entite"))
			{
				scene->AddEntity("NouvelleEntite");
			}

			ImGui::TreePop();
		}
		ImGui::PopID();
	}
#endif
	
}

void SceneMgr::AddScene(std::string name) {
	if (!IsSceneExist(name)) {
		scenes[name] =new  Scene(name);
		Logger::Info("New Scene added to the map");
	}
}

void SceneMgr::RemoveScene(std::string name) {
	if (IsSceneExist(name)) {
		auto pair = scenes.find(name);
		scenes.erase(pair);
		Logger::Info("A scene have been deleted");
	}
}

void SceneMgr::SetActiveScene(std::string name) {
	if (!IsSceneExist(name)) {
		Logger::Warning("The wanted scene does not exist impossible to change the active scene.");
		return;
	}

	if (activeScene == nullptr) {
		activeScene = scenes[name];
		activeScene->OpenScene();
	}
	else{
		activeScene->CloseScene();
		activeScene = scenes[name];
		activeScene->OpenScene();
	}

	Logger::Info("Active Scene changed");
}

bool SceneMgr::IsSceneExist(std::string& name) const
{
	if (scenes.contains(name)) {
		Logger::Warning("A Scene with this name already exist");
		return true;
	}

	return false;
}


