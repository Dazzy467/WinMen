#pragma once
#include <functional>
#include <Windows.h>

class input
{
    public:
    input();
    input(int key);

    void doIfkeyPressed(std::function<void()>F);
    void setKey(int key);

    private:
    bool isPress();
    bool state;
    int key;

};