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
#include "Pbullet.h"
#include"Enemy.h"


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
	//�`��
	void Draw();
	//���
	void Finalize();

private://�����o�ϐ�
	WindowsApp * windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	//�Փ˃}�l�[�W���[
	CollisionManager* collisionManager = nullptr;

	char pla[64];

	SpriteCommon* spriteCommon = nullptr;
	Sprite* tuto = nullptr;
	Sprite* tex = nullptr;
	FbxModel* model1 = nullptr;
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelballet = nullptr;
	FBXobj3d* Otin = nullptr;
	Enemy* cube = nullptr;
	Enemy* DivCube[10];
	Enemy* PartCube[100];
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	FBXobj3d* wall = nullptr;
	FBXobj3d* wall2 = nullptr;
	FBXobj3d* wall3 = nullptr;

	Pbullet* ballet = nullptr;
	
	Player* player = nullptr;

	float CurretmouseX = 0;
	float CurretmouseY = 0;

	float oldposy = 0;

	int bulflag = 0;

	float movex = 0;
	float movey = 0;
	float movez = 0;

	int resetflag = 0;

	XMVECTOR eVel[100];

	XMFLOAT3 Bulpos;


};

