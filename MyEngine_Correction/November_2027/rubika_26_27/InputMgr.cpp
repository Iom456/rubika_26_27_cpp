#include "InputMgr.h"

#include <iostream>
#include <ostream>
#include <SFML/Window/Keyboard.hpp>

std::string UpActionName = "Up";
std::string DownActionName = "Down";
std::string RightActionName = "Right";
std::string LeftActionName = "Left";



void InputMgr::Init()
{
    std::unique_ptr<InputAction> upAction = std::make_unique<InputAction>();

    upAction->SetActionName(UpActionName);
    upAction->SetValue(-1);

    upAction->RegisterCallback("Debug", [](float a)
    {
        std::cout << "Up : " << a << std::endl;
    }, this);

    AddAction(std::move(upAction));
    
    std::unique_ptr<InputAction> downAction = std::make_unique<InputAction>();

    downAction->SetActionName(DownActionName);
    downAction->SetValue(-1);

    downAction->RegisterCallback("Debug", [](float a)
    {
        std::cout << "Down : " << a << std::endl;
    }, this);

    AddAction(std::move(downAction));
    
    std::unique_ptr<InputAction> rightAction = std::make_unique<InputAction>();

    rightAction->SetActionName(RightActionName);
    rightAction->SetValue(-1);

    rightAction->RegisterCallback("Debug", [](float a)
    {
        std::cout << "Right : " << a << std::endl;
    }, this);

    AddAction(std::move(rightAction));
    
    std::unique_ptr<InputAction> leftAction = std::make_unique<InputAction>();

    leftAction->SetActionName(LeftActionName);
    leftAction->SetValue(-1);

    leftAction->RegisterCallback("Debug", [](float a)
    {
        std::cout << "Left : " << a << std::endl;
    }, this);

    AddAction(std::move(leftAction));
}

void InputMgr::Start()
{
   
}

void InputMgr::Update()
{
    GetAction(UpActionName) -> SetValue(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z));
    GetAction(DownActionName) -> SetValue(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
    GetAction(RightActionName) -> SetValue(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
    GetAction(LeftActionName) -> SetValue(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q));

}

void InputMgr::Shut()
{ 
    actions.clear();
}

void InputMgr::AddAction(std::unique_ptr<InputAction> action)
{
    std::string name = action->GetName();
    actions[name] = std::move(action);
}


InputAction* InputMgr::GetAction(const std::string& name)
{
    auto it = actions.find(name);

    if (it == actions.end())
    {
        std::cout << "Action not found: " << name << std::endl;
        return nullptr;
    }

    return it->second.get();
}
