#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "Input.h"

#include "WindowsApp.h"
#include "DXCommon.h"

#include "3d/Object3d.h"
#include "3d/model.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include"2d/PostEffect.h"
#include "DebugText.h"
#include "Audio.h"

#include "fbxsdk.h"
#include "3d/FbxLoader.h"
#include "3d/FBXobj3d.h"
#include "3d/Modelfbx.h"

#include "Camera.h"
#include"Player.h"
#include"PlayerCol.h"


#include"Enemy.h"
#include"Wall.h"




class CollisionManager;

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
	//シーン分岐
	const int& GetScene() { return scene; }
	const int& GettutoScene() { return tutoscene; }
	void SetScene(int scene) { this->scene = scene; }
	//シーン遷移処理
	void transrationScene();
	//描画
	void Draw();
	//
	void restart();
	//解放
	void Finalize();

	//const int& GetScene() { return scene; }

private://メンバ変数
	WindowsApp * Windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	//衝突マネージャー
	CollisionManager* collisionManager = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	

	char pla[64];

	//スプライト
	Sprite* tuto = nullptr;
	Sprite* tex = nullptr;
	Sprite* crosshair = nullptr;

	//3dモデル(地形など)
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelglasswall = nullptr;
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	Wall* glasswallLeft = nullptr;
	Wall* glasswallForward = nullptr;
	
	//1面
	Wall* stage1wall[8];

	//2面
	Wall* stage2wall[6];
	Wall* gunstand = nullptr;
	FbxModel* modelobjgun = nullptr;
	Wall* tutogun = nullptr;
	Wall* stage2Object[3];

	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	//3面
	Wall* stage3wall[3];


	

	//3dモデル(敵)
	//チュートリアル
	Enemy* cube = nullptr;
	Enemy* Stage1[5];
	//ステージ2
	Enemy* Stage2[3];
	//ステージ3
	Enemy* Stage3[5];


	//自機関連
	Player* player = nullptr;
	PlayerCol* playercol = nullptr;
	float movect = 0;
	bool attack = false;

	//ひとつ前のマウスの座標
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//カメラ初期位置
	XMFLOAT3 EyeInitialize = { 0,4,0 };

	//デバッグ用リセットフラグ
	int resetflag = 0;

	//カメラの更新処理用
	int firstfrag = 0;

	float check = 0.01f;

	XMFLOAT3 tutoroateation{ 0.0f,0.0f,0.0f };

	float roat = 0.0f;

	//シーン
	int scene = 1;
	int tutoscene = 0;
	int goflag = 0;
	

};

