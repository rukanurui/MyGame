#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "../Engine/Input.h"

#include "../Engine/WindowsApp.h"
#include "../Engine/DXCommon.h"

#include "../3d/Object3d.h"
#include "../3d/model.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include"../2d/PostEffect.h"
#include "../2d/DebugText.h"
#include "../Engine/Audio.h"

#include "fbxsdk.h"
#include "../3d/FbxLoader.h"
#include "../3d/FBXobj3d.h"
#include "../3d/Modelfbx.h"

#include "../Engine/Camera.h"
#include"../Player/Player.h"
#include"../Collider/PlayerCol.h"

#include"../Enemy/Enemy.h"
#include"../3d/Wall.h"

#include <memory>
#include <list>

#include"BaseScene.h"
#include"TransEffect.h"
#include"StageData.h"



class CollisionManager;

class GameScene : public BaseScene
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
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;
	////敵データ読み込み
	//void LoadEnemyDataS1();
	////敵データ受け取り
	//void SwapEnemyDataS1();
	////地形データ読み込み
	//void LoadWallDataS1();
	////地形データ更新
	//void SwapWallDataS1();
	////敵データ読み込み
	//void LoadEnemyDataS2();
	////敵データ受け取り
	//void SwapEnemyDataS2();
	////地形データ読み込み
	//void LoadWallDataS2();
	////地形データ更新
	//void SwapWallDataS2();
	////敵データ読み込み
	//void LoadEnemyDataS3();
	////敵データ受け取り
	//void SwapEnemyDataS3();
	////地形データ読み込み
	//void LoadWallDataS3();
	////地形データ更新
	//void SwapWallDataS3();
	////敵データ読み込み
	//void LoadEnemyDataS4();
	////敵データ受け取り
	//void SwapEnemyDataS4();
	////地形データ読み込み
	//void LoadWallDataS4();
	////地形データ更新
	//void SwapWallDataS4();
	//更新
	void Update()override;
	//シーン分岐
	const int& GettutoScene() { return tutoscene; }

	//シーン遷移処理
	//void transrationScene();
	//残弾数のgetter
	const int& Getmagazin() { return magazin; };
	//銃を持っているかのgetter
	const bool& Gethave() { return have; };
	//描画
	void Draw()override;
	//解放
	void Finalize()override;

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
	StageData* stagedata = nullptr;
	
	char pla[64];

	//スプライト
	SpriteCommon* spriteCommon = nullptr;
	Sprite* crosshair = nullptr;
	Sprite* gameover = nullptr;
	Sprite* tutomove = nullptr;
	Sprite* tutomouse = nullptr;
	Sprite* tutoshot = nullptr;
	Sprite* tutorule = nullptr;
	Sprite* tutopickup = nullptr;
	Sprite* tutogunpick1 = nullptr;
	Sprite* tutogunpick2 = nullptr;
	Sprite* noammo = nullptr;
	Sprite* trans = nullptr;
	Sprite* tutostage3 = nullptr;
	Sprite* tutothrow = nullptr;
	TransEffect* transEffect = nullptr;

	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ 1280,720 };
	XMFLOAT2 movesize = { 800,300 };

	XMFLOAT2 Effectsize{ 0,0 };
	float transcount = 0;
	bool transscene = false;
	

	bool transfrag = true;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;
	bool noammoflag = false;

	//3dモデル(地形など)
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelglasswall = nullptr;
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	Wall* glasswallLeft = nullptr;
	Wall* glasswallForward = nullptr;

	//オブジェクトのリスト
	std::list<std::unique_ptr<FBXobj3d>> objects;

	//壁のlist
	std::list<std::unique_ptr<Wall>> Walls;

	uint32_t wallNum;
	uint32_t enemyNum;

	//std::list<std::unique_ptr<Wall>> Stage1Walls;
	//std::list<std::unique_ptr<Wall>> Stage2Walls;
	//std::list<std::unique_ptr<Wall>> Stage3Walls;
	//std::list<std::unique_ptr<Wall>> Stage4Walls;
	////壁コマンド
	//std::stringstream wallDataS1;
	//std::stringstream wallDataS2;
	//std::stringstream wallDataS3;
	//std::stringstream wallDataS4;

	//壁のvector
	std::vector<Wall> walls;

	
	//2面
	FbxModel* modelobjgun = nullptr;
	Wall* tutogun = nullptr;
	Wall* stage2Object[3];

	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	
	//3dモデル(敵)

	//敵のリスト
	std::list<std::unique_ptr<Enemy>> Enemys;

	//std::list<std::unique_ptr<Enemy>> Stage1Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage2Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage3Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage4Enemy;
	//
	//敵コマンド
	std::stringstream enemyData;
	//std::stringstream enemyDataS2;
	//std::stringstream enemyDataS3;
	//std::stringstream enemyDataS4;

	//Enemyのvector
	std::vector<Enemy> enemys;

	//チュートリアル
	//std::vector<int> tutonum;
	int tutonum = 0;
	int tutocount = 0;


	//自機関連
	Player* player = nullptr;
	PlayerCol* playercol = nullptr;

	float movect = 0;
	//攻撃したか
	bool attack = false;
	//銃を投げたか
	bool gunthrow = false;
	//銃を持っているか
	bool have = false;
	//残弾数
	int magazin = 0;


	///カメラ関連
	//ひとつ前のマウスの座標
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//カメラ初期位置
	XMFLOAT3 EyeInitialize = { 0,4,0 };
	//デバッグ用リセットフラグ
	int resetflag = 0;
	//カメラの更新処理用
	int firstfrag = 0;
	//プレイヤーが壁にぶつかっているか
	bool wallcol = false;


	//シーン関連
	float timecount = 0;//時間管理酔う変数
	//死んだときのシーン
	int diescene = 0;
	//クリアしたシーン
	int clearscene = 0;
	int tutoscene = 0;
	int goflag = 0;
	

};

