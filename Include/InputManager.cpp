#include "KeyboardInput.cpp"
#include "MouseInput.cpp"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
class InputManager
{
public:
    enum keyState
    {
        Idle,
        Pressed,
        Held,
        Released
    };
    bool setBinds(string Actions,int key);
    void Update();
    void ResetKeyState(int V_Key);
    keyState GetKeyState(int V_Key);
    int WhichKey();
    vector<int> WhichKeyMultiple();
    unordered_map<string,int> keyBinds;
private:
    unordered_map<int, keyState> keyStates;
    unordered_map<int, bool> lastkeyStates;
    set<int> usedKeys;
};

bool InputManager::setBinds(string Actions,int key)
{
    if(usedKeys.find(key) != usedKeys.end()){
        return false;
    }
    keyBinds[Actions] = key;
    usedKeys.insert(key);
    return true;
}
void InputManager::Update()
{
    for (int key = 0x01; key <= 0xFE; ++key)
    {
        bool isPressed = IsKeyDown(key);
        if (isPressed)
        {
            if (!lastkeyStates[key])
            {
                keyStates[key] = Pressed; 
            }
            else
            {
                keyStates[key] = Held; 
            }
        }
        else
        {
            if (lastkeyStates[key])
            {
                keyStates[key] = Released; 
            }
            else
            {
                keyStates[key] = Idle; 
            }
        }
        lastkeyStates[key] = isPressed;
    }
}

void InputManager::ResetKeyState(int V_Key)
{
    keyStates[V_Key] = Idle;
}
InputManager::keyState InputManager::GetKeyState(int V_Key)
{
    return keyStates[V_Key];
}