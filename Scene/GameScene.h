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
	void SwapEnemyData(XMFLOAT3& pos, XMFLOAT3& scale, int& modelname, float& r, bool& mod, int& stage, int& nextflag);
	//地形データ受け取り
	void SwapWallData(XMFLOAT3& pos, XMFLOAT3& scale, XMFLOAT3& rotation, int& modelname, XMFLOAT3& r,int& numcount);
	//const int& GetScene() { return scene; }

	void setepos(XMFLOAT3 pos) { this->enemypos = pos; }
	void setescale(XMFLOAT3 scale) { this->enemyscale = scale; }
	//void setepos(XMFLOAT3 pos) { this->enemypos = pos; }
	//void setepos(XMFLOAT3 pos) { this->enemypos = pos; }

	void setenemynum(int enemynum) { this->enemyNum = enemynum; }

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


	static  int wallNum;
	static  int enemyNum;



	//地形1つ分のデータ
	struct WallData {
		XMFLOAT3 pos{};//座標
		XMFLOAT3 scale{};//スケール
		XMFLOAT3 rotation{};//ローテーション
		int modelname;//モデルの指定
		XMFLOAT3 r;//コライダーの半径指定
		int stage;//ステージの指定
	}walldata;

	static XMFLOAT3 wallpos[];//座標
	static XMFLOAT3 wallscale;//スケール
	static XMFLOAT3 wallrotation;
	static int wallmodelname;//モデルの指定
	static XMFLOAT3 wallr;//コライダーの半径指定

	//std::list<std::unique_ptr<Wall>> Stage1Walls;
	//std::list<std::unique_ptr<Wall>> Stage2Walls;
	//std::list<std::unique_ptr<Wall>> Stage3Walls;
	//std::list<std::unique_ptr<Wall>> Stage4Walls;
	////壁コマンド
	//std::stringstream wallDataS1;
	//std::stringstream wallDataS2;
	//std::stringstream wallDataS3;
	//std::stringstream wallDataS4;

	
	//2面
	FbxModel* modelobjgun = nullptr;
	Wall* tutogun = nullptr;
	Wall* stage2Object[3];

	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	
	//3dモデル(敵)

	//敵のリスト
	std::list<std::unique_ptr<Enemy>> Enemys;

	//敵1体分のデータ
	struct EnemyData {
		XMFLOAT3 pos{0,0,0};//座標
		XMFLOAT3 scale{0,0,0};//スケール
		int modelname=0;//モデルの指定
		float r=0;//コライダーの半径指定
		bool mod=false;//敵の種類の指定
	}enemydata;
	
	static XMFLOAT3 enemypos;//座標
	static XMFLOAT3 enemyscale;//スケール
	static int enemymodelname;//モデルの指定
	static float enemyr;//コライダーの半径指定
	static bool emod;//敵の種類の指定

	//std::list<std::unique_ptr<Enemy>> Stage1Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage2Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage3Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage4Enemy;
	//
	//敵コマンド
	//std::stringstream enemyDataS2;
	//std::stringstream enemyDataS3;
	//std::stringstream enemyDataS4;

	

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

