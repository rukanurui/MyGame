#pragma once

#include"BaseScene.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include <vector>
#include "WindowsApp.h"


class TitleScene:BaseScene
{
protected:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	void Initialize(SpriteCommon* spritecommon);

	void Update();

	void Draw();

	void Finalize();

private:
	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ WindowsApp::window_width,WindowsApp::window_height };
	XMFLOAT2 movesize = { 800,300 };
	bool transfrag = true;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;

};

