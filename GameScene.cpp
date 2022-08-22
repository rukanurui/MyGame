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

    

    //OBJ生成
    Back = model::LoadFromOBJ("skydome");
    //3Dオブジェクト生成
    Backobj = Object3d::Create();
    //モデル紐づけ
    Backobj->SetModel(Back);

    //OBJ生成
    ground = model::LoadFromOBJ("ground");
    //3Dオブジェクト生成
    groundobj = Object3d::Create();
    //モデル紐づけ
    groundobj->SetModel(Back);

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
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("cube");

    Otin = new FBXobj3d;
    Otin->Initialize();
    Otin->SetPosition({ 0.0f,0.0f,0.0f });
    Otin->SetModel(model1);

    cube = new FBXobj3d;
    cube->Initialize();
    cube->SetPosition({ 10.0f,0.0f,0.0f });
    cube->SetModel(model1);

    int counter = 0; // アニメーションの経過時間カウンター

    //Otin->PlayAnimation();
    cube->PlayAnimation();
}

void GameScene::Update()
{

    // マウスの入力を取得
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);

    //スプライト更新
    //obj更新
    Backobj->Update();
    groundobj->Update();
    //FBX更新
    Otin->Update();
    cube->Update();

    camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);

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
    Backobj->Draw();
    groundobj->Draw();

    //objの描画後処理
    Object3d::PostDraw();

    //FBX描画
    Otin->Draw(cmdList);//otintin
    cube->Draw(cmdList);//cube

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
