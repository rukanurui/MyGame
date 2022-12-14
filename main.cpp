
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
    SpriteCommon* spriteCommon = nullptr;

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

    spriteCommon->LoadTexture(1, L"Resources/1432.png");
    spriteCommon->LoadTexture(2, L"Resources/title.png");
    spriteCommon->LoadTexture(3, L"Resources/gameover.png");
    spriteCommon->LoadTexture(4, L"Resources/clear.png");
    spriteCommon->LoadTexture(5, L"Resources/tutomove.png");
    spriteCommon->LoadTexture(6, L"Resources/tutomouse.png");
    spriteCommon->LoadTexture(7, L"Resources/tutoshot.png");
    spriteCommon->LoadTexture(8, L"Resources/tutorule.png");
    spriteCommon->LoadTexture(9, L"Resources/tutoend.png");

    Sprite* crosshair = Sprite::Create(spriteCommon, 1);
    crosshair->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    crosshair->TransferVertexBuffer();

    Sprite* title = Sprite::Create(spriteCommon, 2);
    title->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    title->TransferVertexBuffer();

    Sprite* gameover = Sprite::Create(spriteCommon, 3);
    gameover->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    gameover->TransferVertexBuffer();

    Sprite* clear = Sprite::Create(spriteCommon, 4);
    clear->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    clear->TransferVertexBuffer();

    Sprite* tutomove = Sprite::Create(spriteCommon, 5);
    tutomove->SetPosition({ WindowsApp::window_width / 2,700,0});
    XMFLOAT2 movesize = { 800,300 };
    tutomove->SetSize(movesize);
    tutomove->TransferVertexBuffer();

    Sprite* tutomouse = Sprite::Create(spriteCommon, 6);
    tutomouse->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutomouse->TransferVertexBuffer();

    Sprite* tutoshot = Sprite::Create(spriteCommon, 7);
    tutoshot->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutoshot->TransferVertexBuffer();

    Sprite* tutorule = Sprite::Create(spriteCommon, 8);
    tutorule->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutorule->TransferVertexBuffer();

    Sprite* tutoend = Sprite::Create(spriteCommon, 9);
    tutoend->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutoend->TransferVertexBuffer();


    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

    //ポストエフェクト用テクスチャの読み込み
   /* spriteCommon->LoadTexture(100,L"Resources/White1x1.png");
    int PFnum = 100;*/
    //ポストエフェクトの初期化
    //PostEffect* postEffect = PostEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);
    //postEffect->SetSize({ (float)500.0f,500.0f });
    //postEffect->TransferVertexBuffer();

    //FBXローダーの初期化
    FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
  
    // ゲームシーンの初期化
    gameScene = new GameScene();
    gameScene->Initialize(dxCommon, input, audio,spriteCommon,winApp);

    char pla[64];

    int scene = 0;
    int tutoscene = 0;
    int wait = 0;
    int count = 0;
    
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

        if (scene==0)//タイトル
        {
            title->Update();
            if (input->TriggerKey(DIK_SPACE))
            {
                scene = 2;
                gameScene->SetScene(scene);
            }
        }

        //入力の更新
        input->Update();
        // コマンドリストの取得
        ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

        if (scene==1)//チュートリアル
        {
            //tutoscene = gameScene->GettutoScene();
            if (tutoscene==0)
            {
                if (input->TriggerKey(DIK_SPACE))tutoscene = 1;
            }
            
            if (tutoscene==1)
            {
                wait++;
                if (wait>=5)
                {
                    if (input->TriggerKey(DIK_SPACE))
                    {
                        tutoscene = 2; 
                        wait = 0;
                    }
                }
                
            }
            if (tutoscene == 2)
            {
                wait++;
                if (wait >= 5)
                {
                    if (input->TriggerKey(DIK_SPACE))
                    {
                        tutoscene = 3;
                        wait = 0;
                    }
                }
            }
            if (tutoscene == 3)
            {
                wait++;
                if (wait >= 5)
                {
                    if (input->TriggerKey(DIK_SPACE))
                    {
                        tutoscene = 4;
                        wait = 0;
                    }
                }
            }
            if (tutoscene == 4)
            {
                wait++;
                if (wait >= 5)
                {
                    if (input->TriggerKey(DIK_SPACE))
                    {
                        wait++;
                        if (wait >= 5)
                        {
                            if (input->TriggerKey(DIK_SPACE))
                            {
                                scene = 2;
                                gameScene->SetScene(scene);
                                tutoscene = 0;
                                wait = 0;
                            }
                        }
                    }
                }
            }
            tutomouse->Update();
            tutomove->Update();
            tutoend->Update();
            tutoshot->Update();
            tutorule->Update();
            gameScene->Update();
        }

        if (scene==2)//ゲーム
        {

            if (tutoscene == 0)
            {
                wait++;
                if (wait >= 180&&input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
                {
                    tutoscene = 1;
                    wait = 0;
                }
            }

            if (tutoscene == 1)
            {
                wait++;
                if (wait >= 120)
                {
                    tutoscene = 2;
                    wait = 0;
                }
            }

            if (tutoscene == 2)
            {
                wait++;
                if (wait >= 60)
                {
                    tutoscene = 3;
                    wait = 0;
                }
            }

            crosshair->Update();
            gameScene->Update();
            scene = gameScene->GetScene();

            tutomouse->Update();
            tutomove->Update();
            tutoend->Update();
            tutoshot->Update();
            tutorule->Update();
            gameScene->Update();
        }
        
        //ゲームオーバー
        if (scene==3)
        {
            
            gameScene->Update();
            gameover->Update();
            if (input->TriggerKey(DIK_R))
            {
                //gameScene->Initialize(dxCommon, input, audio, spriteCommon, winApp);
                gameScene->restart();
                scene = 0;
                tutoscene = 0;
                wait = 0;
                count = 0;
            }
        }

        //2面
        if (scene==4)
        {
            
            gameScene->Update();
            clear->Update();
            if (input->TriggerKey(DIK_R))
            {
                gameScene->restart();
                scene = 0;
                tutoscene = 0;
                wait = 0;
                count = 0;
            }
        }

        if (input->PushKey(DIK_ESCAPE))
        {
            break;
        }

        // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

       
        //レンダ―テクスチャへの描画
        //postEffect->PreDrawScene(dxCommon->GetCommandList());

        //postEffect->PostDrawScene(dxCommon->GetCommandList());

        //描画前処理
        dxCommon->PreDraw();


        // ４．描画コマンドここから
        
        // スプライト描画前処理
        

        //obj、スプライトの描画
        //tuto->Draw();

        if (scene != 0)
        {
            gameScene->Draw();
        }

        spriteCommon->PreDraw();

        if (scene == 0)title->Draw();
        if (scene==2)
        {
            if (tutoscene == 0)tutomove->Draw();
            if (tutoscene == 1)tutomouse->Draw();
            if (tutoscene == 2)tutorule->Draw();
        }
        
        if (scene == 2)crosshair->Draw();
        if (scene == 3)gameover->Draw();
        if (scene == 4)clear->Draw();
        

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

        //delete postEffect;

        winApp->Finalize();
        delete winApp;
        winApp = nullptr;

        gameScene->Finalize();
        delete gameScene;

#pragma endregion WindowsAPI後始末

        return 0;
 }