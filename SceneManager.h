#pragma once
#include"BaseScene.h"
#include "Input.h"
#include "DXCommon.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include "WindowsApp.h"
#include "Audio.h"

class SceneManager
{
public:
	//������
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows);
	//�V�[���؂�ւ�
	void NextScene(BaseScene* nextScene) { nextscene = nextScene;}
	//�X�V
	void Update();
	//�`��
	void Draw();

	~SceneManager();

private:

	WindowsApp* Windows = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	BaseScene* scene = nullptr;
	BaseScene* nextscene = nullptr;

	bool transfrag = true;

	
};

