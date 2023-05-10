#pragma once
#include "../Engine/input.h"
#include "../Engine/DXCommon.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include "../Engine/WindowsApp.h"
#include "../Engine/Audio.h"

class SceneManager;

class BaseScene
{
public:

	virtual void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)=0;
	
	virtual void Update()=0;

	virtual void Draw()=0;

	virtual void Finalize()=0;

	virtual ~BaseScene() = default;

	virtual void SetSceneManager(SceneManager* SceneManager) { sceneManager = SceneManager; }

	virtual void SetSlayScene(int scene) { playscene = scene; };

	const int& GetPlayScene() { return playscene; }

private:
	WindowsApp* Windows = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	SpriteCommon* spriteCommon = nullptr;

protected:
	//シーンマネージャー(借りてくる)
	SceneManager* sceneManager = nullptr;

	//どのステージをプレイしているか
	int playscene = 0;
};

