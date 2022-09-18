#pragma once
#include<Windows.h>
#pragma comment (lib, "xinput.lib")
#include <xinput.h>


class pad
{
private:

    int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;//pad十字キー
    int iPad_leftshoulder = 0, iPad_rightshoulder = 0;//padスティック
    int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;//padボタン

public:

    void Update();

    XINPUT_STATE state;

    XINPUT_VIBRATION vibration;//振動

};

