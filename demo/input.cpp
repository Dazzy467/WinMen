#include "input.h"
input::input()
{
    this->key = 0;
    this->state = false;
}

input::input(int key)
{
    this->key = key;
    this->state = false;
}


void input::setKey(int key)
{
    this->key = key;
}

void input::doIfkeyPressed(std::function<void()>F)
{
        if (isPress() && !state)
        {
            state = !state;
            F();
        }else if (!isPress() && state)
        state = !state;
}

bool input::isPress()
{
    return GetKeyState(key) < 0;
}
