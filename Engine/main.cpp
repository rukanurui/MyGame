
#include <vector>
#include <string>


#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "Input.h"

#include "WindowsApp.h"
#include "DXCommon.h"
#include "../3d/Object3d.h"
#include "../3d/model.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include"../2d/PostEffect.h"
#include"../scene/TransEffect.h"
#include "../2d/DebugText.h"
#include "Audio.h"

#include "../3d/FbxLoader.h"

#include "../scene/GameScene.h"
#include "../scene/TitleScene.h"
#include "../scene/BaseScene.h"
#include "../scene/SceneManager.h"



using namespace DirectX;
using namespace Microsoft::WRL;

void spritetrans(XMFLOAT2 size,bool flag);

//GameScene* reset(GameScene* gameScene,DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
//{
//    if (gameScene!=nullptr)
//    {
//        delete gameScene;
//    }
//
//    gameScene = new GameScene;
//    gameScene->Initialize(dxcommon, input, audio, spritecommon, windows);
//    return gameScene;
//}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //ポインタ置き場
    Input* input = nullptr;
    WindowsApp* winApp = nullptr;
    DXCommon* dxCommon = nullptr;
    GameScene* gameScene = nullptr;
    TitleScene * titleScene = nullptr;
    Audio* audio = nullptr;
    Object3d* object3d = nullptr;
    SpriteCommon* spriteCommon = nullptr;
    DebugText* debugText = nullptr;
    SceneManager* sceneManager = nullptr;
    TitleScene* titlescene = nullptr;
    BaseScene* nowScene = nullptr;


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
    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(),dxCommon->GetCommandList(),winApp->window_width,winApp->window_height);
     
//    spriteCommon->LoadTexture(10, L"Resources/debugfont.png");

    // デバッグテキスト初期化
   /* debugText = new DebugText();
    debugText->Initialize(spriteCommon, 10);*/


    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

    //ポストエフェクト用テクスチャの読み込み
    spriteCommon->LoadTexture(100,L"Resources/White1x1.png");
    int PFnum = 100;
    //ポストエフェクトの初期化
    PostEffect* postEffect = PostEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);
    //TransEffect* transEffect = TransEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);
    
    //FBXローダーの初期化
    FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
  
    //シーン関連の初期化
    sceneManager = new SceneManager();
    sceneManager->Initialize(dxCommon, input, audio, spriteCommon, winApp);

    //最初のシーンの生成
    BaseScene* scene = new TitleScene();
    sceneManager->NextScene(scene);

    

    char pla[64];

    int tutoscene = 0;
    int wait = 0;
    int count = 0;

    bool titleflag = true;

   


    
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

        
        sceneManager->Update();
       


        if (input->PushKey(DIK_ESCAPE))
        {
            break;
        }

        // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

       
      

        //レンダ―テクスチャへの描画
        postEffect->PreDrawScene(dxCommon->GetCommandList());
        //transEffect->PreDrawScene(dxCommon->GetCommandList());

        // スプライト描画前処理
        spriteCommon->PreDraw();

        sceneManager->Draw();
        
       
        // ４．描画コマンドここから
        
        

        //obj、スプライトの描画
        //tuto->Draw();
        

        postEffect->PostDrawScene(dxCommon->GetCommandList());
        //transEffect->PostDrawScene(dxCommon->GetCommandList());

        
        //描画前処理
        dxCommon->PreDraw();

        
        //ポストエフェクトの描画
        postEffect->Draw(dxCommon->GetCommandList());
        //transEffect->Draw(dxCommon->GetCommandList());
        

        //gameScene->SpriteDraw();



        //描画後処理
        dxCommon->PostDraw();

        

        // ４．描画コマンドここまで
         

    }
        //解放処理
        delete input;
        delete dxCommon;

        
        delete spriteCommon;


        //オーディオ解放
       /* audio->Finalize();
        delete audio;*/

       //FbxLoader::GetInstance()->Finalize();

        //delete postEffect;

        winApp->Finalize();
        delete winApp;
        winApp = nullptr;

        //gameScene->Finalize();
        delete gameScene;

#pragma endregion WindowsAPI後始末

        return 0;
 }

 void spritetrans(XMFLOAT2 size,bool flag)
 {
     if (flag == true)
     {
         size.x -= 0.3f;
         size.y -= 0.3f;
     }
     else
     {
         size.x += 0.3f;
         size.y += 0.3f;
     }


 }
