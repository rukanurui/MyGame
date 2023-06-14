#pragma once
#include<stdint.h>
#include"../Enemy/Enemy.h"
#include"../3d/Wall.h"
#include <memory>
#include <list>
#include<sstream>


 struct EnemyData {
	uint32_t enemyNum;
	Enemy enemy;
};

struct WallData {
	uint32_t wallNum;
	Wall wall;
};

const uint32_t StageNum = 3;

class StageData
{
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

private:

};









