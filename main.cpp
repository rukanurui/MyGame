
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

void spritetrans(XMFLOAT2 size,bool flag);


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
    DebugText* debugText = nullptr;

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
    spriteCommon->LoadTexture(9, L"Resources/pickuptuto.png");
    spriteCommon->LoadTexture(10, L"Resources/stage2tuto1.png");
    spriteCommon->LoadTexture(11, L"Resources/stage2tuto2.png");
    spriteCommon->LoadTexture(12, L"Resources/noammo.png");
     
//    spriteCommon->LoadTexture(10, L"Resources/debugfont.png");

    // デバッグテキスト初期化
   /* debugText = new DebugText();
    debugText->Initialize(spriteCommon, 10);*/

    //スプライト生成
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
    tutomove->SetPosition({ WindowsApp::window_width / 2,600,0});
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

    Sprite* tutopickup = Sprite::Create(spriteCommon, 9);
    tutopickup->SetPosition({ WindowsApp::window_width / 2,600,0 });
    tutopickup->TransferVertexBuffer();

    Sprite* tutogunpick1 = Sprite::Create(spriteCommon, 10);
    tutogunpick1->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutogunpick1->TransferVertexBuffer();

    Sprite* tutogunpick2 = Sprite::Create(spriteCommon, 11);
    tutogunpick2->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutogunpick2->TransferVertexBuffer();

    Sprite* noammo = Sprite::Create(spriteCommon, 12);
    noammo->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    noammo->TransferVertexBuffer();






    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

    //ポストエフェクト用テクスチャの読み込み
    spriteCommon->LoadTexture(100,L"Resources/White1x1.png");
    int PFnum = 100;
    //ポストエフェクトの初期化
    PostEffect* postEffect = PostEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);
    
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

    //sprite関連
    XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
    XMFLOAT2 spritesize{ 1280,720 };
    bool transfrag = true;
    float spriteangle = 0;
    bool overfrag = true;

    //残弾数
    int magazin = 0;
    bool have = false;
    bool noammoflag = false;
    



    
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
            if (spritesize.x >= 1280)
            {
                transfrag = true;
            }
            if (spritesize.x <= 1000)
            {
                transfrag = false;
            }

            if (transfrag == true)
            {
                spritesize.x -= 0.4f;
                spritesize.y -= 0.3f;
            }
            else
            {
                spritesize.x += 0.4f;
                spritesize.y += 0.3f;
            }

            title->SetRotation(spriteangle);
            title->SetSize(spritesize);
            title->TransferVertexBuffer();
            title->Update();
            if (input->TriggerKey(DIK_SPACE))
            {
                scene = 2;
                tutoscene = 0;
                gameScene->SetScene(scene);
                gameScene->transrationScene();
                spritesize = { 1280,720 };
                transfrag = true;
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
            tutoshot->Update();
            tutorule->Update();
            gameScene->Update();
        }

        if (scene==2)//ゲーム
        {

            if (tutoscene == 0)
            {

                if (movesize.x >= 800)
                {
                    transfrag = true;
                }
                if (movesize.x <= 750)
                {
                    transfrag = false;
                }

                if (transfrag == true)
                {
                    movesize.x -= 0.2f;
                    movesize.y -= 0.2f;
                }
                else
                {
                    movesize.x += 0.2f;
                    movesize.y += 0.2f;
                }

                wait++;
                if (wait >= 180&&input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
                {
                    tutoscene = 1;
                    wait = 0;
                    transfrag = true;
                }
                gameScene->Update();
            }

            if (tutoscene == 1)
            {
                if (spritesize.x >= 1280)
                {
                    transfrag = true;
                }

                if (transfrag == true)
                {
                    spritesize.x -= 1.0f;
                    spritesize.y -= 1.0f;
                }
                wait++;
                if (wait >= 120)
                {
                    tutoscene = 2;
                    spritesize = { 1280,720 };
                    transfrag = true;
                    wait = 0;
                }
            }

            if (tutoscene == 2)
            {
                if (spritesize.x >= 1280)
                {
                    transfrag = true;
                }

                if (transfrag == true)
                {
                    spritesize.x -= 1.0f;
                    spritesize.y -= 1.0f;
                }

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

            tutomouse->SetSize(spritesize);
            tutomove->SetSize(movesize);
            tutoshot->SetSize(spritesize);
            tutorule->SetSize(spritesize);

            tutomouse->TransferVertexBuffer();
            tutomove->TransferVertexBuffer();
            tutoshot->TransferVertexBuffer();
            tutorule->TransferVertexBuffer();

            tutomouse->Update();
            tutomove->Update();
            tutoshot->Update();
            tutorule->Update();
            //debugText->Print()
        }
        
        //ゲームオーバー
        if (scene==3)
        {
            gameScene->Update();

            /*if (overfrag == true)
            {
                spriteangle += 0.3f;

                if (spriteangle >= 45)
                {
                    spriteangle = 45;
                    spritepos.y += 2.0f;
                }

                if (spritepos.y >= 1250) overfrag = false;
            }

            if (overfrag==false)
            {
                spriteangle = 0;
                spritepos.y -= 2.0f;
                if (spritepos.y<=350)
                {
                    spritepos.y = 350;
                }
            }*/

            /*if (overfrag==false&&spritepos.y<= WindowsApp::window_height / 2)
            {
                spritepos.y = WindowsApp::window_height / 2;
            }*/


            gameover->SetRotation(spriteangle);
            gameover->SetPosition(spritepos);
            gameover->TransferVertexBuffer();
            gameover->Update();
            if (input->TriggerKey(DIK_SPACE))
            {
                //gameScene->Initialize(dxCommon, input, audio, spriteCommon, winApp);
                scene = 0;
                tutoscene = 0;
                gameScene->restart();
                wait = 0;
                count = 0;
                spritepos={ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
                spritesize={ 1280,720 };
                transfrag = true;
                spriteangle = 0;
                overfrag = true;
            }
        }

        //クリア
        if (scene==4)
        {
            if (spritesize.x >= 1280)
            {
                transfrag = true;
            }
            if (spritesize.x <= 0.0f)
            {
                transfrag = false;
            }

            if (transfrag == true)
            {
                spritesize.x -= 4.0f;
                spritesize.y -= 3.0f;
            }
            else
            {
                spritesize.x += 4.0f;
                spritesize.y += 3.0f;
            }
            gameScene->Update();
            clear->SetSize(spritesize);
            clear->TransferVertexBuffer();
            clear->Update();
            if (input->TriggerKey(DIK_SPACE))
            {
                
                scene = 5; 
                tutoscene = 3;
                gameScene->SetScene(scene);
                gameScene->transrationScene();
                wait = 0;
                count = 0;
                spritepos = { WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
                spritesize = { 1280,720 };
                transfrag = true;
                spriteangle = 0;
                overfrag = true;
            }
        }

        //ステージ２
        if (scene==5)
        {
            if (tutoscene == 3)
            {
                if (spritesize.x >= 1280)
                {
                    transfrag = true;
                }

                if (transfrag == true)
                {
                    spritesize.x -= 1.0f;
                    spritesize.y -= 1.0f;
                }

                wait++;
                if (wait >= 120)
                {
                    tutoscene = 4;
                    spritesize = { 1280,720 };
                    wait = 0;
                    transfrag = true;
                }
                gameScene->Update();
            }

            if (tutoscene == 4)
            {
                if (spritesize.x >= 1280)
                {
                    transfrag = true;
                }

                if (transfrag == true)
                {
                    spritesize.x -= 1.0f;
                    spritesize.y -= 1.0f;
                }
                wait++;
                if (wait >= 120)
                {
                    tutoscene = 5;
                    spritesize = { 1280,720 };
                    transfrag = true;
                    wait = 0;
                }
            }

            if (tutoscene == 5)
            {
                if (movesize.x >= 800)
                {
                    transfrag = true;
                }
                if (movesize.x <= 750)
                {
                    transfrag = false;
                }

                if (transfrag == true)
                {
                    movesize.x -= 0.2f;
                    movesize.y -= 0.2f;
                }
                else
                {
                    movesize.x += 0.2f;
                    movesize.y += 0.2f;
                }

                wait++;
                if (wait >= 60 && input->PushKey(DIK_SPACE))
                {
                    tutoscene = 6;
                    wait = 0;
                }
            }

            if (tutoscene>=5)
            {
                crosshair->Update();
                gameScene->Update();
                scene = gameScene->GetScene();
                magazin = gameScene->Getmagazin();
                have = gameScene->Gethave();

                if (magazin == 0 && have == true && input->PushKey(DIK_SPACE))
                {
                    noammoflag = true;
                }

                if (noammoflag == true)
                {
                    spritesize.x -= 2.0f;
                    spritesize.y -= 2.0f;
                    wait++;
                }

                if (noammoflag == true && wait >= 100)
                {
                    spritesize = { 1280,720 };
                    noammoflag = false;
                    wait = 0;
                }
            }

            //spriteのサイズ変更処理
            tutopickup->SetSize(movesize);
            tutogunpick1->SetSize(spritesize);
            tutogunpick2->SetSize(spritesize);
            noammo->SetSize(spritesize);
            
            tutopickup->TransferVertexBuffer();
            tutogunpick1->TransferVertexBuffer();
            tutogunpick2->TransferVertexBuffer();
            noammo->TransferVertexBuffer();

            tutopickup->Update();
            tutogunpick1->Update();
            tutogunpick2->Update();
            noammo->Update();
            //debugText->Print()
        }

        //ステージ3
        if (scene==6)
        {
            crosshair->Update();
            gameScene->Update();
            scene = gameScene->GetScene();
            magazin = gameScene->Getmagazin();
        }

        if (input->PushKey(DIK_ESCAPE))
        {
            break;
        }

        // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

       
      

       

        //レンダ―テクスチャへの描画
        postEffect->PreDrawScene(dxCommon->GetCommandList());

        if (scene != 0)
        {
            gameScene->Draw();
        }


        // ４．描画コマンドここから
        
        // スプライト描画前処理
        spriteCommon->PreDraw();

        //obj、スプライトの描画
        //tuto->Draw();

        if (scene == 0)title->Draw();
        if (scene==2)
        {
            if (tutoscene == 0)tutomove->Draw();
            if (tutoscene == 1)tutomouse->Draw();
            if (tutoscene == 2)tutorule->Draw();
        }
        if (scene ==5)
        {
            if (tutoscene == 3)tutogunpick1->Draw();
            if (tutoscene == 4)tutogunpick2->Draw();
            if (tutoscene == 5)tutopickup->Draw();
            if (noammoflag == true)noammo->Draw();
            
        }
        
        if (scene == 3)gameover->Draw();
        if (scene == 4)clear->Draw();
        

        postEffect->PostDrawScene(dxCommon->GetCommandList());

        
        
        //描画前処理
        dxCommon->PreDraw();

        
        //ポストエフェクトの描画
        postEffect->Draw(dxCommon->GetCommandList());

        spriteCommon->PreDraw();
        if (scene !=0)crosshair->Draw();

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

        gameScene->Finalize();
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
