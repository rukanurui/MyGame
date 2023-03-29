#pragma once
#include "Input.h"
#include "DXCommon.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include "WindowsApp.h"
#include "Audio.h"

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

private:
	WindowsApp* Windows = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	SpriteCommon* spriteCommon = nullptr;

protected:
	//シーンマネージャー(借りてくる)
	SceneManager* sceneManager = nullptr;
};

