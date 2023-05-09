#include <Windows.h>
#include <wrl.h>
#include "WindowsApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <dinput.h>


#pragma once
class Input
{
public:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

public: //メンバ関数
	//初期化
	void Initialize(WindowsApp* winApp);
	//更新
	void Update();

	static Input* GetInstance();

	float GetVelx() { return velx;}
	float GetVely() { return vely; }

/// <summary>
/// キーの押下をチェック
/// </summary>
/// <param name = "keyNumber">キー番号(DIK_0など)</param>
/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

/// <summary>
/// キーのトリガーをチェック
/// </summary>
/// <param name = "keyNumber">キー番号(DIK_0など)</param>
/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
/// マウスの押下をチェック
/// </summary>
/// <param name = "keyNumber">マウス番号(DIK_0など)</param>
/// <returns>押されているか</returns>
	bool PushclickLeft();

	//右クリック
	bool PushclickRight();

	/// <summary>
	/// マウスのトリガーをチェック
	/// </summary>
	/// <param name = "keyNumber">マウス番号(DIK_0など)</param>
	/// <returns>トリガーか</returns>
	bool TriggerclickLeft(BYTE mouseNumber);

	void Mousemove();

	MouseMove GetMouseMove();

private: //メンバ変数
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> devkeyboard;
	//マウスのデバイス
	ComPtr<IDirectInputDevice8> devmouse;
	//全キーの入力情報を取得する
	BYTE key[256] = {};
	//前フレームの全キーの入力情報を取得する
	BYTE oldkey[256] = {};
	//マウスの入力情報を取得する
	DIMOUSESTATE mouse;
	//前フレームのマウスの入力情報を取得する
	DIMOUSESTATE oldmouse;
	//インスタンス生成
	ComPtr<IDirectInput8> dinput = nullptr;
	//WindowsAPI
	WindowsApp* winApp = nullptr;

	//マウスx座標
	float mouseX = 0;
	//マウスy座標
	float mouseY = 0;
	//1フレーム前のマウスx座標
	float oldMouseX = 0;
	//1フレーム前のマウスy座標
	float oldMouseY = 0;
	//x軸の移動速度
	float velx = 0;
	//x軸の移動速度
	float vely = 0;

};

