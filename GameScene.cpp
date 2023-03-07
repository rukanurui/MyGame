#pragma once
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include"CollisionManager.h"
#include"Collision.h"
#include"CollisionColor.h"
#include<fstream>


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

    //debugText = new DebugText();
    // デバッグテキスト用のテクスチャ番号を指定
    //const int debugTextTexNumber = 2;
    // デバッグテキスト用のテクスチャ読み込み
    //spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    //debugText->Initialize(spriteCommon, debugTextTexNumber);

    // スプライト共通テクスチャ読み込み
   /* spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");
    spriteCommon->LoadTexture(3, L"Resources/tuto.png");
    spriteCommon->LoadTexture(4, L"Resources/1432.png");*/


    collisionManager = CollisionManager::GetInstance();


    //FBX関連
    //デバイスをセット
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //カメラをセット
    FBXobj3d::SetCamera(camera);
    //FBXパイプライン生成
    FBXobj3d::CreateGraphicsPipeline();
    //file読み込み
    
    //model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");
    modelobjgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");
    //modelglasswall = FbxLoader::GetInstance()->LoadModelFromFile("glasswall");


     //背景
    backsphere = new FBXobj3d;
    backsphere->Initialize();
    backsphere->SetPosition({ 0.0f,0.0f,0.0f });
    backsphere->SetScale({ 1.0f,1.0f,1.0f });
    backsphere->SetRotation({ 0.0f,0.0f,0.0f });
    backsphere->SetModel(modelBack);

    //プレイヤー関連処理
    player = new Player();
    player->Initialize();
    player->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 0.5f));
    player->PlayerInitialize(this->input);
    player->SetPosition({ 0,4,0 });
    player->SetTarget({ 0,4,0 });




    //地形3dオブジェクト
    //床

   /* std::unique_ptr<FBXobj3d>newfloor = std::make_unique<Wall>();
    newfloor->Initialize();
    newfloor->SetPosition({ 0.0f,-1.0f,0.0f });
    newfloor->SetScale({ 1.0f,0.1f,1.0f });
    newfloor->SetModel(modelfloor);
    newfloor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));
    objects.push_back(std::move(newfloor));*/

    
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

   

    ///1面
    LoadWallData();
    SwapWallData();
    //for (int i = 0; i < 8; i++)
    //{
    //   /* std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    //    newwall->Initialize();
    //    newwall->SetModel(modelwall);*/
    //    stage1wall[i] = nullptr;
    //    stage1wall[i] = new Wall();
    //    stage1wall[i]->Initialize();
    //    stage1wall[i]->SetModel(modelwall);
    //}

    //stage1wall[0]->SetPosition({ -10.0f,0.0f,0.0f });//左縦
    //stage1wall[0]->SetScale({ 0.01f,0.5f,0.1f });
    //stage1wall[0]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    //stage1wall[0]->WallInitialize();

    //stage1wall[1]->SetPosition({ 30.0f,0.0f,0.0f });//右縦
    //stage1wall[1]->SetScale({ 0.01f,0.5f,0.5f });
    //stage1wall[1]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,50.0f,0 }, 1.0f));
    //stage1wall[1]->WallInitialize();

    //stage1wall[2]->SetPosition({ 0.0f,0.0f,10.0f });//前くびれ横
    //stage1wall[2]->SetRotation({ 0.0f,90.0f,0.0f });
    //stage1wall[2]->SetScale({ 0.01f,0.5f,0.1f });
    //stage1wall[2]->SetCollider(new BoxCollider(XMVECTOR{ 10.0f,100.0f,0.8f,0 }, 1.0f));
    //stage1wall[2]->WallInitialize();

    //stage1wall[3]->SetPosition({ 0.0f,0.0f,-10.0f });//後ろ横
    //stage1wall[3]->SetScale({ 0.01f,0.5f,1.0f });
    //stage1wall[3]->SetRotation({ 0.0f,90.0f,0.0f });
    //stage1wall[3]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    //stage1wall[3]->WallInitialize();

    //stage1wall[4]->SetPosition({ 10.0f,0.0f,42.5f });//前壁縦長
    //stage1wall[4]->SetScale({ 0.01f,1.0f,0.325f });
    //stage1wall[4]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,32.5f,0 }, 1.0f));
    //stage1wall[4]->WallInitialize();

    //stage1wall[5]->SetPosition({ 20.0f,0.0f,75.0f });//奥横
    //stage1wall[5]->SetScale({ 0.01f,1.0f,0.5f });
    //stage1wall[5]->SetRotation({ 0.0f,90.0f,0.0f });
    //stage1wall[5]->SetCollider(new BoxCollider(XMVECTOR{ 75.0f,100.0f,0.8f,0 }, 1.0f));
    //stage1wall[5]->WallInitialize();

    //stage1wall[6]->SetPosition({ 40.0f,0.0f,50.0f });//奥くびれ横
    //stage1wall[6]->SetScale({ 0.01f,1.0f,0.1f });
    //stage1wall[6]->SetRotation({ 0.0f,90.0f,0.0f });
    //stage1wall[6]->SetCollider(new BoxCollider(XMVECTOR{ 10.0f,100.0f,0.8f,0 }, 1.0f));
    //stage1wall[6]->WallInitialize();

    //stage1wall[7]->SetPosition({ 50.0f,0.0f,70.0f });//奥壁縦
    //stage1wall[7]->SetScale({ 0.01f,1.0f,0.5f });
    //stage1wall[7]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,50.0f,0 }, 1.0f));
    //stage1wall[7]->WallInitialize();

    //壁のスケール0.1=ワールドで10

    //敵関連処理
   
    LoadEnemyData();
    SwapEnemyData();

     
    ///２面
    //壁
    for (int i = 0; i < 6; i++)
    {
        stage2wall[i] = nullptr;
        stage2wall[i] = new Wall();
        stage2wall[i]->Initialize();
        stage2wall[i]->SetModel(modelwall);
    }
    
    //左
    stage2wall[0]->SetPosition({ -30.0f,10.0f,0.0f });
    stage2wall[0]->SetScale({ 0.1f,0.5f,1.0f });
    stage2wall[0]->SetRotation({ 0.0f,0.0f,0.0f });
    stage2wall[0]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    stage2wall[0]->WallInitialize();

    //前
    stage2wall[1]->SetPosition({ 0.0f,0.0f,80.0f });
    stage2wall[1]->SetScale({ 0.1f,1.0f,1.0f });
    stage2wall[1]->SetRotation({ 0.0f,90.0f,0.0f });
    stage2wall[1]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage2wall[1]->WallInitialize();

    //右
    stage2wall[2]->SetPosition({ 70.0f,0.0f,0.0f });
    stage2wall[2]->SetScale({ 0.01f,1.0f,1.0f });
    stage2wall[2]->SetRotation({ 0.0f,0.0f,0.0f });
    stage2wall[2]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,100.0f,0 }, 1.0f));
    stage2wall[2]->WallInitialize();

    //後ろ
    stage2wall[3]->SetPosition({ 0.0f,0.0f,-20.0f });
    stage2wall[3]->SetScale({ 0.1f,1.0f,1.0f });
    stage2wall[3]->SetRotation({ 0.0f,90.0f,0.0f });
    stage2wall[3]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage2wall[3]->WallInitialize();

    //手前横壁
    stage2wall[4]->SetPosition({ -30.0f,0.0f,60.0f });
    stage2wall[4]->SetScale({ 0.1f,1.0f,0.5f });
    stage2wall[4]->SetRotation({ 0.0f,90.0f,0.0f });
    stage2wall[4]->SetCollider(new BoxCollider(XMVECTOR{ 50.0f,100.0f,0.8f,0 }, 1.0f));
    stage2wall[4]->WallInitialize();

    //右縦壁
    stage2wall[5]->SetPosition({ 10.0f,0.0f,0.0f });
    stage2wall[5]->SetScale({ 0.1f,1.0f,0.2f });
    stage2wall[5]->SetRotation({ 0.0f,0.0f,0.0f });
    stage2wall[5]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,20.0f,0 }, 1.0f));
    stage2wall[5]->WallInitialize();


    //銃台座
    gunstand= new Wall();
    gunstand->Initialize();
    gunstand->SetModel(model2);
    gunstand->SetPosition({ 0.0f,0.0f,10.0f });
    gunstand->SetScale({ 0.03f,0.04f,0.03f });
    gunstand->SetRotation({ 0.0f,0.0f,0.0f });
    gunstand->SetCollider(new BoxCollider(XMVECTOR{ 6.0f,6.0f,6.0f,0 }, 1.0f));
    gunstand->WallInitialize();

    //銃本体
    tutogun = new Wall;
    tutogun->Initialize();
    tutogun->SetPosition({ 0.0f,6.0f,10.0f });
    tutogun->SetScale({ 0.01f,0.01f,0.01f });
    tutogun->SetModel(modelobjgun);
    tutogun->SetCollider(new BoxCollider(XMVECTOR{ 6.0f,6.0f,6.0f,0 }, 1.0f));
    tutogun->objgunInitialize();

    //敵2面
    for (int i = 0; i < 3; i++)
    {
        Stage2[i] = nullptr;
        Stage2[i] = new Enemy();
        Stage2[i]->Initialize();
        Stage2[i]->SetScale({ 0.01f,0.01f,0.01f });
        Stage2[i]->SetModel(model2);
    }

    Stage2[0]->SetPosition({ 0.0f, 5.0f, 70.0f });
    Stage2[1]->SetPosition({ 60.0f, 5.0f, 70.0f });
    Stage2[2]->SetPosition({ 60.0f,5.0f,0.0f });

    for (int i = 0; i < 3; i++)
    {
        Stage2[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        Stage2[i]->EnemyInitialize(TRUE);
    }

    ///3面
    //壁
    for (int i = 0; i < 8; i++)
    {
        stage3wall[i] = nullptr;
        stage3wall[i] = new Wall();
        stage3wall[i]->Initialize();
        stage3wall[i]->SetModel(modelwall);
    }

    //左
    stage3wall[0]->SetPosition({ -20.0f,10.0f,0.0f });
    stage3wall[0]->SetScale({ 0.01f,0.5f,1.0f });
    stage3wall[0]->SetRotation({ 0.0f,0.0f,0.0f });
    stage3wall[0]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    stage3wall[0]->WallInitialize();

    //前
    stage3wall[1]->SetPosition({ 0.0f,0.0f,100.0f });
    stage3wall[1]->SetScale({ 0.1f,1.0f,1.0f });
    stage3wall[1]->SetRotation({ 0.0f,90.0f,0.0f });
    stage3wall[1]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage3wall[1]->WallInitialize();

    //右手前縦
    stage3wall[2]->SetPosition({ 20.0f,0.0f,-10.0f });
    stage3wall[2]->SetScale({ 0.01f,1.0f,0.2f });
    stage3wall[2]->SetRotation({ 0.0f,0.0f,0.0f });
    stage3wall[2]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,20.0f,0 }, 1.0f));
    stage3wall[2]->WallInitialize();

    //後ろ
    stage3wall[3]->SetPosition({ 0.0f,0.0f,-20.0f });
    stage3wall[3]->SetScale({ 0.1f,1.0f,1.0f });
    stage3wall[3]->SetRotation({ 0.0f,90.0f,0.0f });
    stage3wall[3]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage3wall[3]->WallInitialize();

    //右手前横壁
    stage3wall[4]->SetPosition({ 30.0f,0.0f,10.0f });
    stage3wall[4]->SetScale({ 0.01f,1.0f,0.1f });
    stage3wall[4]->SetRotation({ 0.0f,90.0f,0.0f });
    stage3wall[4]->SetCollider(new BoxCollider(XMVECTOR{ 15.0f,100.0f,0.8f,0 }, 1.0f));
    stage3wall[4]->WallInitialize();

    //右奥縦壁
    stage3wall[5]->SetPosition({ 20.0f,0.0f,60.0f });
    stage3wall[5]->SetScale({ 0.01f,1.0f,0.4f });
    stage3wall[5]->SetRotation({ 0.0f,0.0f,0.0f });
    stage3wall[5]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,20.0f,0 }, 1.0f));
    stage3wall[5]->WallInitialize();

    //右奥横壁
    stage3wall[6]->SetPosition({ 30.0f,0.0f,20.0f });
    stage3wall[6]->SetScale({ 0.01f,1.0f,0.1f });
    stage3wall[6]->SetRotation({ 0.0f,90.0f,0.0f });
    stage3wall[6]->SetCollider(new BoxCollider(XMVECTOR{ 15.0f,100.0f,0.8f,0 }, 1.0f));
    stage3wall[6]->WallInitialize();

    //右壁
    stage3wall[7]->SetPosition({ 40.0f,0.0f,20.0f });
    stage3wall[7]->SetScale({ 0.01f,1.0f,0.2f });
    stage3wall[7]->SetRotation({ 0.0f,0.0f,0.0f });
    stage3wall[7]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,20.0f,0 }, 1.0f));
    stage3wall[7]->WallInitialize();

    int counter = 0; // アニメーションの経過時間カウンター

}

void GameScene::LoadEnemyData()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyData.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyData << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::SwapEnemyData() {

    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //敵の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    int modelname;//モデルの指定
    float r;//コライダーの半径指定
    bool mod;//敵の種類の指定
    int stage;//ステージの指定
    int nextflag=0;

    //敵のlist追加
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();


    //コマンド実行ループ
    while (getline(enemyData,line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//")==0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION")==0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

            newenemy->SetPosition({ pos.x,pos.y,pos.z});

        }
        else if(word.find("SCALE")==0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

            newenemy->SetScale({ scale.x,scale.y,scale.z});
        }
        else if (word.find("MODEL")==0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname==1)
            {
                newenemy->SetModel(model2);
            }
            
        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(球)の半径指定
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

            newenemy->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, r));
        }
        else if (word.find("SHOT") == 0)
        {
            //敵の種類指定
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
            if (mod==0)
            {
                newenemy->EnemyInitialize(TRUE);
            }
            else if (mod == 1)
            {
                newenemy->EnemyInitialize(FALSE);
            }
        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            if (stage == 1)
            {
                Stage1Enemy.push_back(std::move(newenemy));
            }
            else if (stage == 2)
            {
                Stage2Enemy.push_back(std::move(newenemy));
            }
        }
        else if (word.find("NEXT") == 0)
        {
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

            if (nextflag == 1)
            {
                newenemy = std::make_unique<Enemy>();
                newenemy->Initialize();
            }
        }

        
       
        /*newenemy->SetPosition({ pos.x,pos.y,pos.z });
        newenemy->SetScale({ scale.x,scale.y,scale.z });
        if (modelname==1)
        {
           newenemy->SetModel(model2);
        }
        newenemy->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, r));
        if (mod==0)
        {
            newenemy->EnemyInitialize(TRUE);
        }
        else if (mod == 1)
        {
            newenemy->EnemyInitialize(FALSE);
        }
        if (stage == 1)
        {
            Stage1Enemy.push_back(std::move(newenemy));

        }
        else if (stage == 2)
        {
            Stage2Enemy.push_back(std::move(newenemy));
        }*/

    }
}

void GameScene::LoadWallData()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallData.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallData << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::SwapWallData()
{
    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //壁の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    XMFLOAT3 rotation{};//ローテーション
    int modelname;//モデルの指定
    XMFLOAT3 r;//コライダーの半径指定
    int stage;//ステージの指定
    int nextflag=0;

    //壁のlist追加
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //コマンド実行ループ
    while (getline(wallData, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

            newwall->SetPosition({ pos.x,pos.y,pos.z });

        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

            newwall->SetScale({ scale.x,scale.y,scale.z });
        }
        else if (word.find("ROTAT") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

            newwall->SetRotation({ rotation.x,rotation.y,rotation.z });
        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname == 1)
            {
                newwall->SetModel(modelwall);
            }

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(矩形)の半径指定
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

            newwall->SetCollider(new BoxCollider(XMVECTOR{ r.x,r.y,r.z,0 }, 1.0f));
        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            if (stage == 1)
            {
                newwall->WallInitialize();
                Stage1Walls.push_back(std::move(newwall));
            }
            else if (stage == 2)
            {
                newwall->WallInitialize();
                Stage2Walls.push_back(std::move(newwall));
            }
        }
        else if (word.find("NEXT") == 0)
        {
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

            if (nextflag == 1)
            {
                newwall = std::make_unique<Wall>();
                newwall->Initialize();
            }
        }

    }
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

    //チュートリアル
    if (scene == 1)
    {
        /* if (tutoscene == 0)
         {
             if (input->TriggerKey(DIK_SPACE))goflag = 1;

             if (goflag==1)
             {
                 roat += 1.0f;
                 tutoroateation.x += roat;
                 camera->SetRoatation(tutoroateation);
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                 if (tutoroateation.x >= 90)
                 {
                     roat = 0;
                     goflag = 0;
                     tutoscene = 1;
                 }
             }
         }

         if (tutoscene == 1)
         {
             if (input->TriggerKey(DIK_SPACE))goflag = 1;

             if (goflag == 1)
             {
                 roat += 1.0f;
                 tutoroateation.x += roat;
                 camera->SetRoatation(tutoroateation);
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                 if (tutoroateation.x >= 180)
                 {
                     roat = 0;
                     goflag = 0;
                     tutoscene = 2;
                 }
             }
         }

         if (tutoscene == 2)
         {
             if (input->TriggerKey(DIK_SPACE))goflag = 1;

             if (goflag == 1)
             {
                 roat += 1.0f;
                 tutoroateation.x += roat;
                 camera->SetRoatation(tutoroateation);
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                 if (tutoroateation.x >= 240)
                 {
                     roat = 0;
                     goflag = 0;
                     tutoscene = 3;
                 }
             }
         }
         if (tutoscene == 3)
         {
             if (input->TriggerKey(DIK_SPACE))goflag = 1;

             if (goflag == 1)
             {
                 roat += 1.0f;
                 tutoroateation.x += roat;
                 camera->SetRoatation(tutoroateation);
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                 if (tutoroateation.x >= 240)
                 {
                     roat = 0;
                     goflag = 0;
                     tutoscene = 4;
                 }
             }
         }
         if (tutoscene == 4)
         {
             if (input->TriggerKey(DIK_SPACE))goflag = 1;

             if (goflag == 1)
             {
                 roat += 1.0f;
                 tutoroateation.x += roat;
                 camera->SetRoatation(tutoroateation);
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                 if (tutoroateation.x >= 360)
                 {
                     roat = 0;
                     goflag = 0;
                     tutoscene = 5;
                 }
             }
         }
         if (tutoscene == 5)
         {
             if (input->TriggerKey(DIK_SPACE))
             {
                 scene = 2;
             }

         }*/
         //描画のためにカメラの更新処理を一回呼び出す


        if (firstfrag == 0)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);

            firstfrag = 1;
        }

        floor->Update();
        /*wallLeft->Update();
        wallForward->Update();
        wallRight->Update();
        wallBack->Update();*/
        player->BulUpdate();
        backsphere->Update();
        /*for (int i = 0; i < 20; i++)
        {
         PartCube1[i]->Update();
         PartCube2[i]->Update();
         PartCube3[i]->Update();
         PartCube4[i]->Update();
         PartCube5[i]->Update();
         PartCube6[i]->Update();
        }*/


    }


    //ゲーム本編

    //ステージ１
    if (scene == 2)
    {
        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 1)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 0;

        }


        //FBX更新
        floor->Update();
        player->BulUpdate();
        backsphere->Update();
        player->BulUpdate();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetmatRot());


        for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }


        /*for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Update();
        }*/

        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Update();
        }


        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            //敵更新


            for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Stage1Walls)
            {
                wall->Update();
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

        }


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//マウスだけ動いてる時
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate();
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

            }
        }


        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        if (player->Getwallhit() == 1)
        {
            camera->SetTarget(player->GetTarget());
            camera->SetEye(player->GetPos());
        }



        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            scene = 3;//ゲームオーバー
        }



        for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
        {
            if (enemy->GetScaleX() < check)
            {
                scene = 4;//クリア
            }
        }

    }

    //ステージ２
    if (scene == 5)
    {

        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 0)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 1;
        }

        //FBX更新
        floor->Update();
        for (int i = 0; i < 6; i++)
        {
            stage2wall[i]->Update();
        }
        for (int i = 0; i < 3; i++)
        {
            Stage2[i]->Update();
            Stage2[i]->BulUpdate();
            Stage2[i]->PartUpdate();
        }
        gunstand->Update();
        tutogun->Update();
        player->BulUpdate();
        backsphere->Update();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

        //プレイヤーの銃のフラグ管理
        if (player->Gethave() == false)
        {
            player->Sethave(tutogun->Gethave());
        }
        if (player->Gethave() == true)
        {
            tutogun->Sethave(false);
        }


        //動いていない状態で攻撃したら
        if (input->PushKey(DIK_SPACE) && !input->PushKey(DIK_Q))
        {
            //フラグをtrueにする
            attack = true;
        }

        if (attack == true)
        {
            movect++;

            //敵更新
            for (int i = 0; i < 3; i++)
            {
                Stage2[i]->EnemyUpdate(player->GetPos());
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                attack = false;
                movect = 0;
            }
        }

        //動いていない状態で銃を投げたら
        if (input->PushKey(DIK_Q) && !input->PushKey(DIK_SPACE))
        {
            gunthrow = true;
        }

        if (gunthrow == true)
        {

        }

        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            //敵更新
            for (int i = 0; i < 3; i++)
            {
                Stage2[i]->EnemyUpdate(player->GetPos());
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetmatRot());
            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

        }


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//マウスだけ動いてる時
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate();
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

            }
        }


        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        if (player->Getwallhit() == 1)
        {
            camera->SetTarget(player->GetTarget());
            camera->SetEye(player->GetPos());
            mouseMove.lX = 0;
            mouseMove.lY = 0;
        }



        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            scene = 3;//ゲームオーバー
        }

        //敵を倒したら次のステージ
        //if (cube->GetScaleX() < check &&
        //    Stage1[0]->GetScaleX() < check)
        //    /* Stage1[1]->GetScaleX() < check&&
        //     Stage1[2]->GetScaleX() < check&&
        //     Stage1[3]->GetScaleX() < check&&
        //     Stage1[4]->GetScaleX() < check)*/
        //{
        //    scene = 4;//クリア
        //}
    }

    //ステージ3
    if (scene == 6)
    {

        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 0)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 1;
        }

        //FBX更新
        floor->Update();
        for (int i = 0; i < 8; i++)
        {
            stage3wall[i]->Update();
        }

        for (int i = 0; i < 3; i++)
        {
            Stage2[i]->Update();
            Stage2[i]->BulUpdate();
            Stage2[i]->PartUpdate();
        }


        player->BulUpdate();
        backsphere->Update();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetmatRot());
        tutogun->Update();

        //プレイヤーの銃のフラグ管理
        if (player->Gethave() == false)
        {
            player->Sethave(tutogun->Gethave());
        }
        if (player->Gethave() == true)
        {
            tutogun->Sethave(false);
        }


        //動いていない状態で攻撃したら
        if (input->PushKey(DIK_SPACE) && !input->PushKey(DIK_Q))
        {
            //フラグをtrueにする
            attack = true;
        }

        if (attack == true)
        {
            movect++;

            ////敵更新
            //for (int i = 0; i < 3; i++)
            //{
            //    Stage2[i]->EnemyUpdate(player->GetPos());
            //}

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                attack = false;
                movect = 0;
            }
        }

        //動いていない状態で銃を投げたら
        if (input->PushKey(DIK_Q) && !input->PushKey(DIK_SPACE))
        {
            gunthrow = true;
        }

        if (gunthrow == true)
        {

        }

        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            ////敵更新
            //for (int i = 0; i < 3; i++)
            //{
            //    Stage2[i]->EnemyUpdate(player->GetPos());
            //}

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetmatRot());
            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

        }


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//マウスだけ動いてる時
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate();
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

            }
        }


        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        if (player->Getwallhit() == 1)
        {
            camera->SetTarget(player->GetTarget());
            camera->SetEye(player->GetPos());
            mouseMove.lX = 0;
            mouseMove.lY = 0;
        }



        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            scene = 3;//ゲームオーバー
        }

        //敵を倒したら次のステージ
        //if (cube->GetScaleX() < check &&
        //    Stage1[0]->GetScaleX() < check)
        //    /* Stage1[1]->GetScaleX() < check&&
        //     Stage1[2]->GetScaleX() < check&&
        //     Stage1[3]->GetScaleX() < check&&
        //     Stage1[4]->GetScaleX() < check)*/
        //{
        //    scene = 4;//クリア
        //}
    }

    //ゲームオーバー
    if (scene == 3)
    {
        //FBX更新
        floor->Update();
       /* for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Update();
        }*/
        player->BulUpdate();
        backsphere->Update();

    }

    //クリア
    if (scene == 4)
    {
        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 0)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);

            firstfrag = 1;
        }

        //FBX更新
        floor->Update();

        player->BulUpdate();
        //backsphere->Update();





     //sprintf_s(pla, "WASD : move");

     //debugText->Print(pla, 0, 0, 1.0f);

    }
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
    if (scene==2)
    {
       /* for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Draw(cmdList);
        }*/
        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Draw(cmdList);
        }
    }

    //ステージオブジェクト
    floor->Draw(cmdList);
    if (scene == 5)
    {
        for (int i = 0; i < 6; i++)
        {
            stage2wall[i]->Draw(cmdList);
        }

        gunstand->Draw(cmdList);
        tutogun->Draw(cmdList);
    }

    if (scene==6)
    {
        for (int i = 0; i < 8; i++)
        {
            stage3wall[i]->Draw(cmdList); 
        }

        tutogun->Draw(cmdList);
    }
    
   
  

    //敵関連
    
    if (scene==2)
    {
        for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
        {
            enemy->BulDraw(cmdList);
            enemy->PartDraw(cmdList);
            enemy->Draw(cmdList);
        }
        
    }

    if (scene==5)
    {
        for (int i = 0; i < 3; i++)
        {
            Stage2[i]->Draw(cmdList); 
            Stage2[i]->PartDraw(cmdList);
            Stage2[i]->BulDraw(cmdList);
        }
    }

    if (scene==3)
    {
        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Draw(cmdList);
        }
        floor->Draw(cmdList);
    }

    if (scene == 4)
    {
        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Draw(cmdList);
        }
        floor->Draw(cmdList);
    }
     
    

    //プレイヤー関連
     player->throwgunDraw(cmdList);
     player->gunDraw(cmdList);
     player->BulDraw(cmdList);
    // player->meleeDraw(cmdList);
    

    // デバッグテキスト描画
    //debugText->DrawAll();
}

void GameScene::restart()
{
  

    firstfrag = 1;

    //プレイヤー関連処理
   /* ballet->SetPosition({ 500.0f,5.0f,0.0f });
    ballet->SetScale({ 0.01f,0.01f,0.01f });
    ballet->SetModel(modelballet);
   
    ballet->BulInitialize();*/

    player->Initialize();
    
    player->PlayerInitialize(this->input);
    player->SetPosition({ 0,4,0 });
    player->SetTarget({ 0,4,0 });
    player->sethit(0);


    XMFLOAT3 eyepos{ 0.0f, 4.0f, 0.0f };
    camera->SetEye(eyepos);
    camera->SetTarget(eyepos);

    //camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);
   


    //敵関連処理
   

    //FBX更新
    player->BulUpdate();
    backsphere->Update();

   
  /*  for (int i = 0; i < 2; i++)
    {
        Stage1[i]->Update();
        Stage1[0]->BulUpdate();
    }*/
    /*for (int i = 0; i < 8; i++)
    {
        stage1wall[i]->Update();
    }*/


}

void GameScene::transrationScene()
{
    if (scene==2)
    {
        //camera->SetEye(EyeInitialize);
        player->Sethave(true);
        /*LoadEnemyData();
        SwapEnemyData();*/

        for (int i = 0; i < 6; i++)
        {
            stage2wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage2wall[i]->SetScale({ 0.01f,0.01f,0.01f });
            gunstand->SetPosition({ -1000.0f,10.0f,0.0f });
            tutogun->SetPosition({ 0.0f,0.0f,20.0f });
            stage2wall[i]->Update();
            gunstand->Update();
            tutogun->Update();
        }
        for (int i = 0; i < 8; i++)
        {
            stage3wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage3wall[i]->SetScale({ 0.01f,0.01f,0.01f });
            stage3wall[i]->Update();
        }
    }

    if (scene==5)
    {
        const XMFLOAT3 respos={0,0,0};
        player->Sethave(false);
        player->SetPosition(respos);
        camera->SetEye(respos);

        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage3wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            //Stage1[0]->
            stage3wall[i]->Update();
            stage1wall[i]->Update();
        }
    }

    if (scene==6)
    {
        const XMFLOAT3 respos = { 0,0,0 };
        player->Sethave(false);
        player->SetPosition(respos);
        camera->SetEye(respos);

        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage1wall[i]->SetScale({ 0.01f,0.01f,0.01f });
            stage1wall[i]->Update();
        }

        for (int i = 0; i < 6; i++)
        {
            stage2wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage2wall[i]->SetScale({ 0.01f,0.01f,0.01f });
            gunstand->SetPosition({ -1000.0f,10.0f,0.0f });
            tutogun->SetPosition({ 0.0f,0.0f,20.0f });
            stage2wall[i]->Update();
            gunstand->Update();
            tutogun->Update();
        }
    }
    
}
 

void GameScene::Finalize()
{
    //3dオブジェクト解放
    //delete object3d;
    //3dモデル解放
    //delete Model;

    //デバッグテキスト解放
    //debugText->Finalize();
    delete debugText;

    //スプライト解放
    //for (auto& sprite : sprites) {
    //    delete sprite;
    //}
    //sprites.clear();

    delete camera;
    //delete Windows;
    //delete input;
    /*delete dxCommon;
    delete audio;*/
    delete model2;
    delete modelfloor;
    delete modelwall;
    delete modelBack;
    delete floor;
    delete backsphere;

    delete player;


    for (int i = 0; i < 3; i++)
    {
        delete Stage2[i];
    }

    for (int i = 0; i < 8; i++)
    {
        delete stage1wall[i];
    }
    for (int i = 0; i < 4; i++)
    {
        delete stage2wall[i];
    }

}
