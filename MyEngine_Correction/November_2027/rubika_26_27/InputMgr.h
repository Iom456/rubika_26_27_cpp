#pragma once
#include <vector>
#include <InputAction.h>
#include <map>
#include <memory>

class InputMgr 
{
public:
    
    void Init();
    void Start();
    void Update();
    void Shut();
    
    void AddAction(std::unique_ptr<InputAction> action);
    InputAction* GetAction(const std::string& name);
    
private:
    std::unordered_map<std::string, std::unique_ptr<InputAction>> actions;
    
};
