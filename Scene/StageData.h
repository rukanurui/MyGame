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

protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

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

	//�f�[�^����
	void InsertData(int stagenum,int enemynum, std::list<std::unique_ptr<Enemy>> enemy, int wallnum, std::list<std::unique_ptr<Wall>> wall,int tuto);
	

private:

	//3d���f��(�n�`�Ȃ�)
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

	//�I�u�W�F�N�g�̃��X�g
	std::list<std::unique_ptr<FBXobj3d>> objects;

	//�ǂ�list
	std::list<std::unique_ptr<Wall>> Stage1Walls;
	std::list<std::unique_ptr<Wall>> Stage2Walls;
	std::list<std::unique_ptr<Wall>> Stage3Walls;
	std::list<std::unique_ptr<Wall>> Stage4Walls;
	//�ǃR�}���h
	std::stringstream wallDataS1;
	std::stringstream wallDataS2;
	std::stringstream wallDataS3;
	std::stringstream wallDataS4;

	//�ǂ�vector
	//std::vector<Wall> walls;

	//�G�̃��X�g
	std::list<std::unique_ptr<Enemy>> Stage1Enemy;
	std::list<std::unique_ptr<Enemy>> Stage2Enemy;
	std::list<std::unique_ptr<Enemy>> Stage3Enemy;
	std::list<std::unique_ptr<Enemy>> Stage4Enemy;

	//�G�R�}���h
	std::stringstream enemyDataS1;
	std::stringstream enemyDataS2;
	std::stringstream enemyDataS3;
	std::stringstream enemyDataS4;

	//Enemy��vector
	//std::vector<Enemy> enemys;

	//�`���[�g���A��
	std::vector<int> tutonum;

	//const uint32_t StageNum = 3;
};









