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
	//初期化
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows);
	//シーン切り替え
	void NextScene(BaseScene* nextScene) { nextscene = nextScene;}
	//更新
	void Update();
	//描画
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

