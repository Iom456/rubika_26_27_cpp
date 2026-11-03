#include "InputMgr.h"

#include <iostream>
#include <ostream>
#include <SFML/Window/Keyboard.hpp>

std::string jumpActionName = "Jump";
InputAction jumpAction;


void InputMgr::Init()
{
    jumpAction.SetActionName(jumpActionName);
    jumpAction.SetValue(-1);
    jumpAction.RegisterCallback("Debug", [](float a)
    {
        std::cout << a << std::endl;
    }, this);
    AddAction(&jumpAction);
    
}

void InputMgr::Start()
{
}

void InputMgr::Update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
       GetAction(jumpActionName)->SetValue(1);
    else 
        GetAction(jumpActionName) -> SetValue(-1);
}

void InputMgr::Shut()
{
    actions.clear();
}

void InputMgr::AddAction( InputAction* action)
{
    actions[action->GetName()] = action;
}


InputAction* InputMgr::GetAction(std::string name)
{
    if (actions[name] != nullptr)
        return actions[name];
    return nullptr;
}
