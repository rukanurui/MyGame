#pragma once
#include <xinput.h>
#pragma comment (lib, "xinput.lib")

class pad
{
private:



public:


    int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;//pad十字キー
    int iPad_leftshoulder = 0, iPad_rightshoulder = 0;//padスティック
    int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;//padボタン

    //１フレーム前
    int Old_iPad_left = 0, Old_iPad_right = 0, iOld_Pad_up = 0, Old_iPad_down = 0;
    int Old_iPad_leftshoulder = 0, Old_iPad_rightshoulder = 0;
    int Old_iPad_A = 0, Old_iPad_B = 0, Old_iPad_X = 0, Old_iPad_Y = 0;


    XINPUT_STATE state;
    XINPUT_VIBRATION vibration;//振動

    void Update();

    void PreUpdate();
};

