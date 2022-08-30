#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>


using namespace DirectX;

void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon,WindowsApp*windows)
{
    //ポインタ置き場
    
    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->windows = windows;



    //カメラ生成
    camera = new Camera(this->input,this->windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height,this->input);


#pragma region 描画初期化処理


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

    
    //スプライトの生成


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
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("wall");
    modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");

    Otin = new FBXobj3d;
    Otin->Initialize();
    Otin->SetPosition({ 0.0f,0.0f,0.0f });
    Otin->SetModel(model1);

    cube = new FBXobj3d;
    cube->Initialize();
    cube->SetPosition({ 10.0f,0.0f,10.0f });
    cube->SetModel(model2);

    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetModel(modelfloor);

    floor2 = new FBXobj3d;
    floor2->Initialize();
    floor2->SetPosition({ -11.3f,0.5f,0.2f });
    floor2->SetModel(modelfloor);
         
    wall = new FBXobj3d;
    wall->Initialize();
    wall->SetPosition({ 3.0f,18.0f,18.0f });
    wall->SetModel(modelwall);

    wall2 = new FBXobj3d;
    wall2->Initialize();
    wall2->SetPosition({ -10.0f,18.0f,18.0f });
    wall2->SetModel(modelwall);

    ballet = new FBXobj3d;
    ballet->Initialize();
    ballet->SetPosition({ 0.0f,5.0f,0.0f });
    ballet->SetModel(modelballet);

    int counter = 0; // アニメーションの経過時間カウンター

    Otin->PlayAnimation();
    //cube->PlayAnimation();
}

void GameScene::Update()
{

    // マウスの入力を取得
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);

    if (bulflag == 0)
    {
        bulpos = camera->GetEye();
        bulpos.z -= 1.0f;
    }

    //スプライト更新
    
    //FBX更新

    //cube->SetPosition({movex,movey,movez});

    Otin->Update();
    cube->Update();
    floor->Update();
    floor2->Update();
    wall->Update();
    wall2->Update();
    ballet->Update();

    camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);

    //ゲーム本編
    if (input->PushKey(DIK_SPACE))
    {
        bulflag = 1;
    }

    if (bulflag==1)
    {
        bulpos.z += 0.1f;
        ballet->SetPosition(bulpos);
        if (bulpos.z >= 20)
        {
           bulflag = 0;
        }
    }

}

void GameScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    //obj描画前処理
    Object3d::PreDraw(dxCommon->GetCommandList());
    // スプライト描画前処理
    //spriteCommon->PreDraw();

    //obj、スプライトの描画
    
    //objの描画後処理
    Object3d::PostDraw();

    //FBX描画
    Otin->Draw(cmdList);//otintin
    cube->Draw(cmdList);//cube
    floor->Draw(cmdList);
   // floor2->Draw(cmdList);
    wall->Draw(cmdList);
    //wall2->Draw(cmdList);

    if (bulflag==1) ballet->Draw(cmdList);

    // デバッグテキスト描画
    //debugText->DrawAll();
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

    delete Otin;
    delete model1;
    delete cube;
    delete model2;
}
