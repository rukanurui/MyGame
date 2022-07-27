#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��

#include "Input.h"

#include "WindowsApp.h"
#include "DXCommon.h"

#include "Object3d.h"
#include "model.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include"2d/PostEffect.h"
#include "DebugText.h"
#include "Audio.h"

#include "fbxsdk.h"
#include "FbxLoader.h"

#include "FBXobj3d.h"
#include "Modelfbx.h"
#include "Camera.h"
#include "GameScene.h"
#include"WindowsApp.h"

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
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	FbxModel* model1 = nullptr;
	FbxModel* model2 = nullptr;
	FBXobj3d* Otin = nullptr;
	FBXobj3d* cube = nullptr;
	Object3d* object3d = object3d->Create();
	model* Model = model::LoadFromOBJ("skydome");

	//����p�ϐ�

	XMFLOAT3 Pos{ 0,0,0 };//���W
	
	XMFLOAT3 Velocity{ 0,0,0 };//���x

	XMFLOAT3 adsVelocity{ 0,0,0 };//�����_���x

	XMFLOAT3 cameraroatation{ 0,0,0 };

};

