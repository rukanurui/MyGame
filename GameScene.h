#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��

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
#include"Player/Player.h"
#include"Collider/PlayerCol.h"

#include"Enemy/Enemy.h"
#include"Wall.h"

#include <memory>
#include <list>
#include<sstream>

#include"BaseScene.h"




class CollisionManager;

class GameScene :BaseScene
{
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�����o�֐�

	//������
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;
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
	//�X�V
	void Update()override;
	//�V�[������
	const int& GetScene() { return scene; }
	const int& GettutoScene() { return tutoscene; }
	void SetScene(int scene) { this->scene = scene; }
	//�V�[���J�ڏ���
	void transrationScene();
	//�c�e����getter
	const int& Getmagazin() { return magazin; };
	//�e�������Ă��邩��getter
	const bool& Gethave() { return have; };
	//�`��
	void Draw()override;
	//
	void restart();
	//���
	void Finalize()override;

	//const int& GetScene() { return scene; }

private://�����o�ϐ�
	WindowsApp * Windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	//�Փ˃}�l�[�W���[
	CollisionManager* collisionManager = nullptr;
	
	char pla[64];

	//�X�v���C�g
	SpriteCommon* spriteCommon = nullptr;
	Sprite* crosshair = nullptr;
	Sprite* title = nullptr;
	Sprite* gameover = nullptr;
	Sprite* clear = nullptr;
	Sprite* tutomove = nullptr;
	Sprite* tutomouse = nullptr;
	Sprite* tutoshot = nullptr;
	Sprite* tutorule = nullptr;
	Sprite* tutopickup = nullptr;
	Sprite* tutogunpick1 = nullptr;
	Sprite* tutogunpick2 = nullptr;
	Sprite* noammo = nullptr;

	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ 1280,720 };
	XMFLOAT2 movesize = { 800,300 };
	bool transfrag = true;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;
	bool noammoflag = false;

	//3d���f��(�n�`�Ȃ�)
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelglasswall = nullptr;
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	Wall* glasswallLeft = nullptr;
	Wall* glasswallForward = nullptr;

	//�I�u�W�F�N�g�̃��X�g
	std::list<std::unique_ptr<FBXobj3d>> objects;

	//�ǂ�list
	std::list<std::unique_ptr<Wall>> Stage1Walls;
	std::list<std::unique_ptr<Wall>> Stage2Walls;
	//�ǃR�}���h
	std::stringstream wallDataS1;
	std::stringstream wallDataS2;

	//1��
	Wall* stage1wall[8];

	//2��
	Wall* stage2wall[6];
	Wall* gunstand = nullptr;
	FbxModel* modelobjgun = nullptr;
	Wall* tutogun = nullptr;
	Wall* stage2Object[3];

	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	//3��
	Wall* stage3wall[8];

	//3d���f��(�G)

	//�G�̃��X�g
	std::list<std::unique_ptr<Enemy>> Stage1Enemy;
	std::list<std::unique_ptr<Enemy>> Stage2Enemy;
	
	//�G�R�}���h
	std::stringstream enemyDataS1;
	std::stringstream enemyDataS2;

	//�X�e�[�W2
	Enemy* Stage2[3];
	//�X�e�[�W3
	Enemy* Stage3[5];


	//���@�֘A
	Player* player = nullptr;
	PlayerCol* playercol = nullptr;

	float movect = 0;
	//�U��������
	bool attack = false;
	//�e�𓊂�����
	bool gunthrow = false;
	//�e�������Ă��邩
	bool have = false;
	//�c�e��
	int magazin = 0;

	//�ЂƂO�̃}�E�X�̍��W
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//�J���������ʒu
	XMFLOAT3 EyeInitialize = { 0,4,0 };

	//�f�o�b�O�p���Z�b�g�t���O
	int resetflag = 0;

	//�J�����̍X�V�����p
	int firstfrag = 0;

	float check = 0.01f;

	XMFLOAT3 tutoroateation{ 0.0f,0.0f,0.0f };

	float roat = 0.0f;

	//�V�[��
	int scene = 0;
	int tutoscene = 0;
	int goflag = 0;
	

};

