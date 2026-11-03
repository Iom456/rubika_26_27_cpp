﻿#include "InputMgr.h"

#include <iostream>
#include <ostream>
#include <SFML/Window/Keyboard.hpp>


void InputMgr::Init()
{
    std::string jumpActionName = "Jump";
    InputAction jumpAction;
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
    //GetAction("Jump")->SetValue(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
}

void InputMgr::Shut()
{
    actions.clear();
}

void InputMgr::AddAction( InputAction* action)
{
    if (GetAction(action->GetName()) == nullptr)
    {
        actions.push_back(action);
    }
}


InputAction* InputMgr::GetAction(std::string name)
{
    for (auto action : actions)
    {
        if (action->GetName() == name)
            return action;
    }
    return nullptr;
}
