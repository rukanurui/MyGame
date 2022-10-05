#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "Input.h"

#include "WindowsApp.h"
#include "DXCommon.h"

#include "Object3d.h"
#include "model.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include"2d/PostEffect.h"
#include "DebugText.h"
#include "Audio.h"

#include "fbxsdk.h"
#include "FbxLoader.h"

#include "FBXobj3d.h"
#include "Modelfbx.h"
#include "Camera.h"
#include"Player.h"
#include "Pbullet.h"



class GameScene
{
protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://メンバ関数

	//初期化
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon,WindowsApp*windows);
	//更新
	void Update();
	//描画
	void Draw();
	//解放
	void Finalize();

private://メンバ変数
	WindowsApp * windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	Player* player = nullptr;


	SpriteCommon* spriteCommon = nullptr;
	FbxModel* model1 = nullptr;
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelballet = nullptr;
	FBXobj3d* Otin = nullptr;
	FBXobj3d* cube = nullptr;
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	FBXobj3d* wall = nullptr;
	FBXobj3d* wall2 = nullptr;
	FBXobj3d* ballet = nullptr;
	
	Player* player = nullptr;
	Pbullet* bullet = nullptr;

	float CurretmouseX = 0;
	float CurretmouseY = 0;

	float oldposy = 0;

	XMFLOAT3 bulpos;
	int bulflag = 0;

	float movex = 0;
	float movey = 0;
	float movez = 0;


};

