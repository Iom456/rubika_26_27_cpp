#pragma once
#include <vector>
#include <InputAction.h>
#include <map>

class InputMgr 
{
public:
    
    void Init();
    void Start();
    void Update();
    void Shut();
    
    void AddAction(InputAction* action);
    InputAction* GetAction(std::string name);
    
private:
    std::vector<InputAction*> actions;
    
};