#include <Windows.h>
#include <iostream>
#include <vector>
bool IsMouseKeyDown(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}

POINT GetMousePosition() {
    POINT point;
    GetCursorPos(&point);
    return point;
}

int WhichClickUniversal(){
    for (int click = 0x01; click <= 0xFE; ++click) {
        if (IsMouseKeyDown(click)) {
            return click; 
        }
    }
    return 0; 
}
std::vector<int> WhichClickUniversalMultiple(){
    std::vector<int> MultiClicks;
        for (int key = 0x01; key <= 0xFE; ++key) {
        if (IsMouseKeyDown(key)) {
            MultiClicks.push_back(key);
        }
    }
    return MultiClicks;
}