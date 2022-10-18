
#include <vector>
#include <string>


#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

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

#include "3d/FbxLoader.h"

#include "GameScene.h"



using namespace DirectX;
using namespace Microsoft::WRL;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //ポインタ置き場
    Input* input = nullptr;
    WindowsApp* winApp = nullptr;
    DXCommon* dxCommon = nullptr;
    GameScene* gameScene = nullptr;
    Audio* audio = nullptr;
    Object3d* object3d = nullptr;

#pragma region WindowsAPI初期化
    winApp = new WindowsApp();
    winApp->Initialize();
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理
    // DirectX初期化処理　ここから
    dxCommon = new DXCommon();
    dxCommon->Initialize(winApp);

    //入力の初期化
    input = new Input();
    input->Initialize(winApp);

    //オーディオの初期化
     audio = new Audio();
     audio->Initialize();

     /*  XAudio2VoiceCallback voiceCallback;*/

    // Object3d静的初期化
     Object3d::StaticInitialize(dxCommon->GetDevice(), WindowsApp::window_width, WindowsApp::window_height);

    // スプライト共通部分の初期化
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(),dxCommon->GetCommandList(),winApp->window_width,winApp->window_height);

    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

    //ポストエフェクト用テクスチャの読み込み
    spriteCommon->LoadTexture(100,L"Resources/White1x1.png");
    int PFnum = 100;
    //ポストエフェクトの初期化
    PostEffect* postEffect = PostEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);
    //postEffect->SetSize({ (float)500.0f,500.0f });
    //postEffect->TransferVertexBuffer();

    //FBXローダーの初期化
    FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
  
    // ゲームシーンの初期化
    gameScene = new GameScene();
    gameScene->Initialize(dxCommon, input, audio,spriteCommon,winApp);
    
#pragma endregion 描画初期化処理

    while (true)  // ゲームループ
    {
#pragma region ウィンドウメッセージ処理
        if (winApp->ProcessMessage())
        {
            break;
        }

#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
        // DirectX毎フレーム処理　ここから

        //入力の更新
        input->Update();
        // コマンドリストの取得
        ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

        gameScene->Update();

        // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

       
        //レンダ―テクスチャへの描画
        //postEffect->PreDrawScene(dxCommon->GetCommandList());

        //postEffect->PostDrawScene(dxCommon->GetCommandList());

        //描画前処理
        dxCommon->PreDraw();

        // ４．描画コマンドここから
        
        gameScene->Draw();

        //ポストエフェクトの描画
        //postEffect->Draw(dxCommon->GetCommandList());


        // ４．描画コマンドここまで
         //描画後処理
        dxCommon->PostDraw();

    }
        //解放処理
        delete input;
        delete dxCommon;

        
        delete spriteCommon;


        //オーディオ解放
       /* audio->Finalize();
        delete audio;*/

       //FbxLoader::GetInstance()->Finalize();

        delete postEffect;

        winApp->Finalize();
        delete winApp;
        winApp = nullptr;

        gameScene->Finalize();
        delete gameScene;

#pragma endregion WindowsAPI後始末

        return 0;
 }