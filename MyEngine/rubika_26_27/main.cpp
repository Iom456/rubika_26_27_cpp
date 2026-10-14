#include <SFML/Graphics.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>


#include <Globals.h>
#include <Profiler.h>
#include <Logger.h>
#include <DebugMgr.h>
#include <TextureMgr.h>
#include "SceneMgr.h"

int main()
{
    gData.Init();

    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "SFML works!", sf::State::Windowed);

    ImGui::SFML::Init(window);

   /* Logger::Info("This is an info message. That is useful");
    Logger::Warning("This is a warning message. Should I worry?");
    Logger::Error("This is an error message. Oh sh*t!!");*/

    sf::Clock clock;
    clock.restart();

   

    SceneMgr scene_mgr;
    scene_mgr.Initialize();
    scene_mgr.AddScene("TestScene");
    
    if (gData.TextureManager->LoadTexture("D:/Fork/rubika_26_27_cpp_forked/MyEngine/Ressources/Antonio_Belpaese.xml", "Animations"))
    {
        Logger::Info("Have load texture");
    }

    if (gData.TextureManager->LoadTexture("D:/Fork/rubika_26_27_cpp_forked/MyEngine/Ressources/enemy_texture_2.xml", "Animations"))
    {
        Logger::Info("Have load texture");
    }
    if (gData.TextureManager->LoadTexture("D:/Fork/rubika_26_27_cpp_forked/MyEngine/Ressources/Basement.xml", "Backgrounds"))
    {
        Logger::Info("Have load texture");
    }

    while (window.isOpen())
    {
        gData.IncrementFrameCount();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLACK, "Frame %llu", gData.FrameCount);

        int deltaTimeMicroS = clock.getElapsedTime().asMicroseconds();
        float fDeltaTimeMS = (float)deltaTimeMicroS / 1000.f;
        float fDeltaTimeS = fDeltaTimeMS / 1000.f;
        sf::Time imGuiTime = clock.restart();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLUE, "Event & Input");
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

#ifdef _USE_IMGUI
            ImGui::SFML::ProcessEvent(window, event.value());
            //scene_mgr.DrawDebug();
#endif
        }

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_RED, "Update");
#ifdef _USE_IMGUI
        ImGui::SFML::Update(window, imGuiTime);
        
       
        
#endif

        // sample
        //ImGui::ShowDemoWindow();
        //Logger::DrawLogger();
        gData.DebugMgr->Draw();

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Draw");
        window.clear();
#ifdef _USE_IMGUI
        ImGui::SFML::Render(window);
#endif
        window.display();

        PROFILER_EVENT_END();

        PROFILER_EVENT_END();
    }

    ImGui::SFML::Shutdown();

    scene_mgr.Shut();
    gData.Shut();
    gData.Destroy();

    return 0;
}