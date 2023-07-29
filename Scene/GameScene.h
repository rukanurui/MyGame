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
	//敵データ受け取り
	void SwapEnemyData(XMFLOAT3& pos, XMFLOAT3& scale, int& modelname, float& r, bool& mod);
	//地形データ受け取り
	void SwapWallData(XMFLOAT3& pos, XMFLOAT3& scale, XMFLOAT3& rotation, int& modelname, XMFLOAT3& r,int& numcount);
	//const int& GetScene() { return scene; }

	void setenemynum(int &enemynum) { this->enemyNum = enemynum; }

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
	Sprite* Wtuto = nullptr;
	Sprite* lefttuto = nullptr;
	Sprite* tutotime = nullptr;
	Sprite* tutopickup = nullptr;
	Sprite* tutogunpick1 = nullptr;
	Sprite* tutogunpick2 = nullptr;
	Sprite* noammo = nullptr;
	Sprite* trans = nullptr;
	Sprite* tutostage3 = nullptr;
	Sprite* tutothrow = nullptr;
	Sprite* play = nullptr;
	Sprite* stop = nullptr;
	Sprite* ammo = nullptr;
	Sprite* ammoone[5];
	TransEffect* transEffect = nullptr;

	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ 1280,720 };
	XMFLOAT2 movesize = { 800,300 };
	XMFLOAT2 ammosize{ 200.0f,200.0f };
	XMFLOAT2 ammoonesize{ 50.0f,100.0f };

	XMFLOAT2 Effectsize{ 0,0 };
	float transcount = 0;
	bool transscene = false;
	

	bool transfrag = true;
	bool playflag = false;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;
	bool noammoflag = false;

	//3dモデル(地形など)
	FbxModel* model2 = nullptr;
	FbxModel* modelenemy = nullptr;
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


	static  int wallNum;
	static  int enemyNum;

	std::vector<XMFLOAT3> wallpos;//座標
	std::vector<XMFLOAT3> wallscale;//スケール
	std::vector<XMFLOAT3> wallrotation;//ローテーション
	std::vector<int>  wallmodelname;//モデルの指定
	std::vector<XMFLOAT3> wallr;//コライダーの半径指定

	
	//2面
	FbxModel* modelobjgun = nullptr;
	Wall* tutogun = nullptr;
	Wall* stage2Object[3];

	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	
	//3dモデル(敵)

	//敵のリスト
	std::list<std::unique_ptr<Enemy>> Enemys;

	
	std::vector<XMFLOAT3> enemypos;//座標
	std::vector<XMFLOAT3> enemyscale;//スケール
	std::vector<int>  enemymodelname;//モデルの指定
	std::vector<float> enemyr;//コライダーの半径指定
	std::vector<bool> enemymod;//敵の種類の指定


	//チュートリアル
	//std::vector<int> tutonum;
	static int tutonum;
	int tutocount = 0;


	//自機関連
	Player* player = nullptr;
	PlayerCol* playercol = nullptr;

	float movect = 0;
	//攻撃したか
	bool attack = false;
	//銃を投げたか
	bool gunthrow = false;
	//銃を拾うアクションをしたか
	bool gunpick = false;
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

