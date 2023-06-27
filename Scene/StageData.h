#pragma once
#include<stdint.h>
#include"../Enemy/Enemy.h"
#include"../3d/Wall.h"
#include <memory>
#include <list>
#include<sstream>
#include <string>


const uint32_t StageNum = 3;

class StageData
{

protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	//敵データ読み込み
	void LoadEnemyDataS1();
	//敵データ受け取り
	void SwapEnemyDataS1();
	//地形データ読み込み
	void LoadWallDataS1();
	//地形データ更新
	void SwapWallDataS1();
	//敵データ読み込み
	void LoadEnemyDataS2();
	//敵データ受け取り
	void SwapEnemyDataS2();
	//地形データ読み込み
	void LoadWallDataS2();
	//地形データ更新
	void SwapWallDataS2();
	//敵データ読み込み
	void LoadEnemyDataS3();
	//敵データ受け取り
	void SwapEnemyDataS3();
	//地形データ読み込み
	void LoadWallDataS3();
	//地形データ更新
	void SwapWallDataS3();
	//敵データ読み込み
	void LoadEnemyDataS4();
	//敵データ受け取り
	void SwapEnemyDataS4();
	//地形データ読み込み
	void LoadWallDataS4();
	//地形データ更新
	void SwapWallDataS4();

	//データ整理
	void InsertData(int stagenum,int enemynum, std::list<std::unique_ptr<Enemy>> enemy, int wallnum, std::list<std::unique_ptr<Wall>> wall,int tuto);
	

private:

	//3dモデル(地形など)
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;

	struct Stagedata {
		uint32_t enemyNum;
		std::list<std::unique_ptr<Enemy>> Enemy;
		uint32_t wallNum;
		std::list<std::unique_ptr<Wall>> Walls;
		uint32_t tutoNum;
	}deta;

	//オブジェクトのリスト
	std::list<std::unique_ptr<FBXobj3d>> objects;

	//壁のlist
	std::list<std::unique_ptr<Wall>> Stage1Walls;
	std::list<std::unique_ptr<Wall>> Stage2Walls;
	std::list<std::unique_ptr<Wall>> Stage3Walls;
	std::list<std::unique_ptr<Wall>> Stage4Walls;
	//壁コマンド
	std::stringstream wallDataS1;
	std::stringstream wallDataS2;
	std::stringstream wallDataS3;
	std::stringstream wallDataS4;

	//壁のvector
	//std::vector<Wall> walls;

	//敵のリスト
	std::list<std::unique_ptr<Enemy>> Stage1Enemy;
	std::list<std::unique_ptr<Enemy>> Stage2Enemy;
	std::list<std::unique_ptr<Enemy>> Stage3Enemy;
	std::list<std::unique_ptr<Enemy>> Stage4Enemy;

	//敵コマンド
	std::stringstream enemyDataS1;
	std::stringstream enemyDataS2;
	std::stringstream enemyDataS3;
	std::stringstream enemyDataS4;

	//Enemyのvector
	//std::vector<Enemy> enemys;

	//チュートリアル
	std::vector<int> tutonum;

	//const uint32_t StageNum = 3;
};









