#pragma once
#include<stdint.h>
#include"../Enemy/Enemy.h"
#include"../3d/Wall.h"
#include <memory>
#include <list>
#include<sstream>
#include <string>
#include"GameScene.h"



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

	StageData();

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
	void InsertData(int stagenum,int tuto,int enemynum,int wallnum);
	

private:

	GameScene* gamescene = nullptr;


	//壁コマンド
	std::stringstream wallDataS1;
	std::stringstream wallDataS2;
	std::stringstream wallDataS3;
	std::stringstream wallDataS4;

	//敵コマンド
	std::stringstream enemyDataS1;
	std::stringstream enemyDataS2;
	std::stringstream enemyDataS3;
	std::stringstream enemyDataS4;

	uint32_t enemyNum;
	uint32_t wallNum;


	//Enemyのvector
	//std::vector<Enemy> enemys;

	//チュートリアル
	std::vector<int> tutonum;

	//const uint32_t StageNum = 3;
};









