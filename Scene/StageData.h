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
	//�G�f�[�^�ǂݍ���
	void LoadEnemyDataS1();
	//�G�f�[�^�󂯎��
	void SwapEnemyDataS1();
	//�n�`�f�[�^�ǂݍ���
	void LoadWallDataS1();
	//�n�`�f�[�^�X�V
	void SwapWallDataS1();
	//�G�f�[�^�ǂݍ���
	void LoadEnemyDataS2();
	//�G�f�[�^�󂯎��
	void SwapEnemyDataS2();
	//�n�`�f�[�^�ǂݍ���
	void LoadWallDataS2();
	//�n�`�f�[�^�X�V
	void SwapWallDataS2();
	//�G�f�[�^�ǂݍ���
	void LoadEnemyDataS3();
	//�G�f�[�^�󂯎��
	void SwapEnemyDataS3();
	//�n�`�f�[�^�ǂݍ���
	void LoadWallDataS3();
	//�n�`�f�[�^�X�V
	void SwapWallDataS3();
	//�G�f�[�^�ǂݍ���
	void LoadEnemyDataS4();
	//�G�f�[�^�󂯎��
	void SwapEnemyDataS4();
	//�n�`�f�[�^�ǂݍ���
	void LoadWallDataS4();
	//�n�`�f�[�^�X�V
	void SwapWallDataS4();

private:

};









