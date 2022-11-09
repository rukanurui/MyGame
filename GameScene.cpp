#pragma once
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include"CollisionManager.h"
#include"Collision.h"
#include"CollisionColor.h"


using namespace DirectX;

void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon,WindowsApp*windows)
{
    //ポインタ置き場
    
    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->Windows = windows;



    //カメラ生成
    camera = new Camera(this->input,this->Windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height,this->input);


#pragma region 描画初期化処理


    //spriteCommon = new SpriteCommon();
    //spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    debugText = new DebugText();
    // デバッグテキスト用のテクスチャ番号を指定
    const int debugTextTexNumber = 2;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    // スプライト共通テクスチャ読み込み
    spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");
    spriteCommon->LoadTexture(3, L"Resources/tuto.png");
    spriteCommon->LoadTexture(4, L"Resources/1432.png");

    
    //スプライトの生成
    //Sprite* tuto = Sprite::Create(spriteCommon, 3);
    //tuto->SetPosition({ 0,0,0 });
    //tuto->SetRotation({ (float)(rand() % 360) });
    //tuto->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //tuto->TransferVertexBuffer();

    //Sprite* tex = Sprite::Create(spriteCommon, 1);
    //tex->SetPosition({ 100,100,0 });
    //tex->SetRotation({ (float)(rand() % 360) });
    //tuto->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //tex->TransferVertexBuffer();

    //Sprite* crosshair = Sprite::Create(spriteCommon, 4);
    //crosshair->Create(spriteCommon, 4);
    //crosshair->SetPosition({Windows->window_width/2,Windows->window_height/2,0 });
    ///*crosshair->SetRotation({ (float)(rand() % 360) });*/
    //tuto->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //crosshair->TransferVertexBuffer();




    collisionManager = CollisionManager::GetInstance();


    //FBX関連
    //デバイスをセット
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //カメラをセット
    FBXobj3d::SetCamera(camera);
    //FBXパイプライン生成
    FBXobj3d::CreateGraphicsPipeline();
    //file読み込み
    
    model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");

    //地形3dオブジェクト
    //床
    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

         
    //壁
    wall = new Wall;
    wall->Initialize();
    wall->SetPosition({ -30.0f,10.0f,0.0f });
    wall->SetScale({ 0.1f,0.5f,1.0f });
    wall->SetRotation({ 0.0f,0.0f,0.0f });
    wall->SetModel(modelwall);
    wall->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    wall->WallInitialize();

    wall2 = new Wall;
    wall2->Initialize();
    wall2->SetPosition({ 0.0f,0.0f,100.0f });
    wall2->SetScale({ 0.1f,1.0f,1.0f });
    wall2->SetRotation({ 0.0f,90.0f,0.0f });
    wall2->SetModel(modelwall);
    wall2->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    wall2->WallInitialize();

    wall3 = new Wall;
    wall3->Initialize();
    wall3->SetPosition({ 100.0f,0.0f,0.0f });
    wall3->SetScale({ 0.01f,0.1f,0.1f });
    wall3->SetRotation({ 0.0f,0.0f,0.0f });
    wall3->SetModel(modelwall);
    wall3->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,100.0f,0 }, 1.0f));
    wall3->WallInitialize();

    //プレイヤー関連処理
    ballet = new Pbullet;
    ballet->Initialize();
    ballet->SetPosition({ 500.0f,5.0f,0.0f });
    ballet->SetScale({ 0.01f,0.01f,0.01f });
    ballet->SetModel(modelballet);
    ballet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
    ballet->BulInitialize();
    
    player = new Player(ballet);
    player->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);
    player->PlayerInitialize(this->input);
    

    //敵関連処理
    cube = new Enemy;
    cube->Initialize();
    cube->SetPosition({ 5.0f,5.0f,20.0f });
    cube->SetScale({ 0.01f,0.01f,0.01f });
    cube->SetModel(model2);
    cube->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 },1.0f));
    cube->EnemyInitialize();

    for (int i = 0; i < 5; i++)
    {
        Stage1[i] = nullptr;
        Stage1[i] = new Enemy;
        Stage1[i]->Initialize();
        Stage1[i]->SetScale({0.01f,0.01f,0.01f});
        Stage1[i]->SetModel(model2);
    }

    Stage1[0]->SetPosition({ 15.0f,5.0f,10.0f });
    Stage1[1]->SetPosition({ 15.0f,10.0f,10.0f });
    Stage1[2]->SetPosition({ 10.0f,5.0f,20.0f });
    Stage1[3]->SetPosition({ 35.0f,5.0f,5.0f });
    Stage1[4]->SetPosition({ 25.0f,10.0f,30.0f });

    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        Stage1[i]->EnemyInitialize();
    }

    //particle
    for (int i = 0; i < 20; i++)
    {
        PartCube1[i] = nullptr;
        PartCube1[i] = new PartEnemy;
        PartCube1[i]->Initialize();
        PartCube1[i]->SetPosition({ 5.0f,5.0f,20.0f });
        PartCube1[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube1[i]->SetModel(model2);
        PartCube1[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube1[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube2[i] = nullptr;
        PartCube2[i] = new PartEnemy;
        PartCube2[i]->Initialize();
        PartCube2[i]->SetPosition({ 15.0f,5.0f,10.0f });
        PartCube2[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube2[i]->SetModel(model2);
        PartCube2[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube2[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube3[i] = nullptr;
        PartCube3[i] = new PartEnemy;
        PartCube3[i]->Initialize();
        PartCube3[i]->SetPosition({ 15.0f,10.0f,10.0f });
        PartCube3[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube3[i]->SetModel(model2);
        PartCube3[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube3[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube4[i] = nullptr;
        PartCube4[i] = new PartEnemy;
        PartCube4[i]->Initialize();
        PartCube4[i]->SetPosition({ 10.0f,5.0f,20.0f });
        PartCube4[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube4[i]->SetModel(model2);
        PartCube4[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube4[i]->PartInitialize();
    }  

    for (int i = 0; i < 20; i++)
    {
        PartCube5[i] = nullptr;
        PartCube5[i] = new PartEnemy;
        PartCube5[i]->Initialize();
        PartCube5[i]->SetPosition({ 35.0f,5.0f,5.0f });
        PartCube5[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube5[i]->SetModel(model2);
        PartCube5[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube5[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube6[i] = nullptr;
        PartCube6[i] = new PartEnemy;
        PartCube6[i]->Initialize();
        PartCube6[i]->SetPosition({ 25.0f,10.0f,30.0f });
        PartCube6[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube6[i]->SetModel(model2);
        PartCube6[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube6[i]->PartInitialize();
    }


    int counter = 0; // アニメーションの経過時間カウンター



}

void GameScene::Update()
{

    if (input->PushKey(DIK_R))
    {
        resetflag = 1;
    }

    // マウスの入力を取得
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);
    player->SetmouseX(CurretmouseX);
    player->SetmouseY(CurretmouseY);

    //スプライト更新
    //tex->Update();
    //tuto->Update();
    //crosshair->Update();
    
    
    //FBX更新

    
    floor->Update();
    wall->Update();
    wall2->Update();
    wall3->Update();
    cube->Update();

    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->Update();
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube1[i]->Update();
        PartCube2[i]->Update();
        PartCube3[i]->Update();
        PartCube4[i]->Update();
        PartCube5[i]->Update();
        PartCube6[i]->Update();
    }

    camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);

    

    //ゲーム本編
    
    player->PlayerUpdate();

    //ballet->Update();
    
    cube->EnemyUpdate();

    XMFLOAT3 bulpos = ballet->GetPos();
    XMFLOAT3 epos = cube->GetPos();

    for (int i = 0; i < 20; i++)
    {
        PartCube1[i]->PartUpdate(cube->GetPos());
        PartCube2[i]->PartUpdate(Stage1[0]->GetPos());
        PartCube3[i]->PartUpdate(Stage1[1]->GetPos());
        PartCube4[i]->PartUpdate(Stage1[2]->GetPos());
        PartCube5[i]->PartUpdate(Stage1[3]->GetPos());
        PartCube6[i]->PartUpdate(Stage1[4]->GetPos());
    }



    //すべての衝突をチェック
    collisionManager->CheckAllCollisions();

    if (resetflag==1)
    {
        for (int i = 0; i < 10; i++)
        {
            PartCube1[i]->SetPosition({ 100.0f + 1.0f * i,5.0f,20.0f });
            //PartCube1[i]->colReset();
        }
        cube->SetPosition({ 5.0f,5.0f,20.0f });
        resetflag = 0;
    }


    //sprintf_s(pla, "WASD : move");

    //debugText->Print(pla, 0, 0, 1.0f);

}

void GameScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    //obj描画前処理
    Object3d::PreDraw(dxCommon->GetCommandList());
    //// スプライト描画前処理
    //spriteCommon->PreDraw();

    ////obj、スプライトの描画
    ////tuto->Draw();
    //crosshair->Draw();
    //objの描画後処理
    Object3d::PostDraw();

    //FBX描画

    //ステージオブジェクト
    floor->Draw(cmdList);
    wall->Draw(cmdList);
    wall2->Draw(cmdList);
    wall3->Draw(cmdList);

    //敵関連
    cube->Draw(cmdList);//cube
    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->Draw(cmdList);
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube1[i]->Draw(cmdList);
        PartCube2[i]->Draw(cmdList);
        PartCube3[i]->Draw(cmdList);
        PartCube4[i]->Draw(cmdList);
        PartCube5[i]->Draw(cmdList);
        PartCube6[i]->Draw(cmdList);
    }

    ////プレイヤー関連
    ballet->Draw(cmdList);

    

    // デバッグテキスト描画
    debugText->DrawAll();
}

    

void GameScene::Finalize()
{
    //3dオブジェクト解放
    //delete object3d;
    //3dモデル解放
    //delete Model;

    //デバッグテキスト解放
    debugText->Finalize();
    delete debugText;

    //スプライト解放
    //for (auto& sprite : sprites) {
    //    delete sprite;
    //}
    //sprites.clear();

    delete model1;
    delete cube;
    delete model2;
}
