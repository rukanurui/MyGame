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
#include"Player.h"
#include"PlayerCol.h"

#include "Pbullet.h"
#include"Enemy.h"
#include"PartEnemy.h"
#include"Wall.h"




class CollisionManager;

class GameScene
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
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon,WindowsApp*windows);
	//�X�V
	void Update();
	//�V�[������
	const int& GetScene() { return scene; }
	const int& GettutoScene() { return tutoscene; }
	void SetScene(int scene) { this->scene = scene; }
	//�`��
	void Draw();

	void restart();
	//���
	void Finalize();

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
	SpriteCommon* spriteCommon = nullptr;
	

	char pla[64];

	//�X�v���C�g
	Sprite* tuto = nullptr;
	Sprite* tex = nullptr;
	Sprite* crosshair = nullptr;

	//3d���f��(�n�`�Ȃ�)
	FbxModel* model1 = nullptr;
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelballet = nullptr;
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	Wall* wallLeft = nullptr;
	Wall* wallForward = nullptr;
	Wall* wallTute = nullptr;
	Wall* wallRight = nullptr;
	Wall* wallBack = nullptr;



	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	//3d���f��(�G)
	Enemy* cube = nullptr;
	Enemy* Stage1[5];
	PartEnemy* PartCube1[20];
	PartEnemy* PartCube2[20];
	PartEnemy* PartCube3[20];
	PartEnemy* PartCube4[20];
	PartEnemy* PartCube5[20];
	PartEnemy* PartCube6[20];
	
	//���@�֘A
	Pbullet* ballet = nullptr;
	Player* player = nullptr;
	PlayerCol* playercol = nullptr;

	//�ЂƂO�̃}�E�X�̍��W
	float CurretmouseX = 0;
	float CurretmouseY = 0;

	//�f�o�b�O�p���Z�b�g�t���O
	int resetflag = 0;

	//�J�����̍X�V�����p
	int firstfrag = 0;

	float check = 0.01f;

	XMFLOAT3 tutoroateation{ 0.0f,0.0f,0.0f };

	float roat = 0.0f;

	//�V�[��
	int scene = 1;
	int tutoscene = 0;
	int goflag = 0;

};

