#include "InputAction.h"

InputAction::InputAction(const std::string& name) : ActionNameHash(name.size())
{
    SetActionName(name);
}

void InputAction::SetActionName(const std::string& name)
{
    ActionName = name;
}

void InputAction::SetValue(float value)
{
    Value = value;
}

void InputAction::RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner)
{
    sCallbackInfo newCallbackInfo;
    newCallbackInfo.DebugName = debugName;
    newCallbackInfo.Callback = callback;
    newCallbackInfo.Owner = owner;
    
    Callbacks.push_back(newCallbackInfo);
}

void InputAction::UnregisterCallbacks(void* owner)
{
    for (int i = 0; i < Callbacks.size(); i++)
    {
        if (Callbacks[i].Owner == owner)
            Callbacks.erase(Callbacks.begin() + i);
    }
}

void InputAction::Callback()
{
    for (auto& callback : Callbacks)
    {
        callback.Callback(Value);
    }
}
