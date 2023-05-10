#include "SceneManager.h"


void SceneManager::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
	this->dxCommon = dxcommon;
	this->input = input;
	this->audio = audio;
	this->spriteCommon = spritecommon;
	this->Windows = windows;

}

void SceneManager::Update()
{
	//シーン切り替え
	//次シーンの予約があるなら
	if (nextscene)
	{
		//古いシーンの終了
		if (scene)
		{
			scene->Finalize();
			delete scene;
		}

		//シーン切り替え
		scene = nextscene;
		nextscene = nullptr;

		//シーンマネージャーをセット
		scene->SetSceneManager(this);

		//次のシーンを初期化する
		scene->Initialize(dxCommon,input,audio,spriteCommon,Windows);

		

		
	}

	//シーン更新
	scene->Update();

}

void SceneManager::Draw()
{
	scene->Draw();
}


SceneManager::~SceneManager()
{
	//シーンの終了と解放
	scene->Finalize();
	delete scene;
}