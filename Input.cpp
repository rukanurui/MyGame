#include "Input.h"



#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;


void Input::Initialize(WindowsApp* winApp)
{

    HRESULT result;

    this->winApp = winApp;

    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

    //ComPtr<IDirectInputDevice8> devkeyboard = nullptr;
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
    result = dinput->CreateDevice(GUID_SysMouse, &devmouse, NULL);
    //入力データ形式のセット
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); //標準形式
    result = devmouse->SetDataFormat(&c_dfDIMouse); //標準形式
    //排他制御レベルのセット
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

    result = devmouse->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{

    HRESULT result;

    //前回のキー入力を保存
    memcpy(oldkey, key, sizeof(key));
    
    //キーボード情報の取得開始
    result = devkeyboard->Acquire();
    
    result = devkeyboard->GetDeviceState(sizeof(key), key);

    //マウス情報の取得開始
    result = devmouse->Acquire();
    //前回のマウス入力を保存
    oldmouse = mouse;

    SetCursorPos(990, 540);

    ShowCursor(FALSE);

    result = devmouse->GetDeviceState(sizeof(mouse), &mouse);
}

Input* Input::GetInstance()
{
    static Input instance;

    return &instance;
}

bool Input::PushKey(BYTE keyNumber)
{
    //指定キーを押していればtrueを返す
    if (key[keyNumber]) {
        return true;
    }
    //そうでなければfalse
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //前回押してなく、今回押している
    if (!oldkey[keyNumber] && key[keyNumber]) {
        return true;
    }
    //そうでなければfalse
    return false;
}

bool Input::PushclickLeft()
{
    if (mouse.rgbButtons[0])
    {
        return true;
    }
    return false;
}

bool Input::PushclickRight()
{
    if (mouse.rgbButtons[1])
    {
        return true;
    }
    return false;
}

bool Input::TriggerclickLeft(BYTE mouseNumber)
{
    if (!oldmouse.rgbButtons[0] && mouse.rgbButtons[0])
    {
        return true;
    }
    return false;
}

void Input::Mousemove()
{
    if (mouse.lX > 0) velx = 0.1f;

    if (mouse.lX < 0)velx = -0.1f;

}

Input::MouseMove Input::GetMouseMove()
{
    MouseMove tmp;
    tmp.lX = mouse.lX;
    tmp.lY = mouse.lY;
    tmp.lZ = mouse.lZ;
    return tmp;
}



