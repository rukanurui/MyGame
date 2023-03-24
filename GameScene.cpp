#pragma once
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include"Collider/CollisionManager.h"
#include"Collider/Collision.h"
#include"Collider/CollisionColor.h"
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


    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    // スプライト共通テクスチャ読み込み
    spriteCommon->LoadTexture(1, L"Resources/1432.png");
    //spriteCommon->LoadTexture(2, L"Resources/title.png");
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

    //スプライト生成
    
    crosshair = Sprite::Create(spriteCommon, 1);
    crosshair->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    crosshair->TransferVertexBuffer();

    gameover = Sprite::Create(spriteCommon, 3);
    gameover->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    gameover->TransferVertexBuffer();

    clear = Sprite::Create(spriteCommon, 4);
    clear->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    clear->TransferVertexBuffer();

    tutomove = Sprite::Create(spriteCommon, 5);
    tutomove->SetPosition({ WindowsApp::window_width / 2,600,0 });
    tutomove->SetSize(movesize);
    tutomove->TransferVertexBuffer();

    tutomouse = Sprite::Create(spriteCommon, 6);
    tutomouse->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutomouse->TransferVertexBuffer();

    tutoshot = Sprite::Create(spriteCommon, 7);
    tutoshot->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutoshot->TransferVertexBuffer();

    tutorule = Sprite::Create(spriteCommon, 8);
    tutorule->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutorule->TransferVertexBuffer();

    tutopickup = Sprite::Create(spriteCommon, 9);
    tutopickup->SetPosition({ WindowsApp::window_width / 2,600,0 });
    tutopickup->TransferVertexBuffer();

    tutogunpick1 = Sprite::Create(spriteCommon, 10);
    tutogunpick1->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutogunpick1->TransferVertexBuffer();

    tutogunpick2 = Sprite::Create(spriteCommon, 11);
    tutogunpick2->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutogunpick2->TransferVertexBuffer();

    noammo = Sprite::Create(spriteCommon, 12);
    noammo->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    noammo->TransferVertexBuffer();



    //debugText = new DebugText();
    // デバッグテキスト用のテクスチャ番号を指定
    //const int debugTextTexNumber = 2;
    // デバッグテキスト用のテクスチャ読み込み
    //spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    //debugText->Initialize(spriteCommon, debugTextTexNumber);
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
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

   

    /////1面
    //LoadWallDataS1();
    //SwapWallDataS1();

    ////壁のスケール0.1=ワールドで10

    ////敵関連処理
   
    //LoadEnemyDataS1();
    //SwapEnemyDataS1();

     
    ///２面
   
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

void GameScene::LoadEnemyDataS1()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS1.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS1 << file.rdbuf();

    //ファイルを閉じる
    //先頭に戻る
    file.close();
    file.clear();
    file.seekg(0, std::ios::beg);
    
    
}

void GameScene::LoadWallDataS1()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS1.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS1 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::LoadEnemyDataS2()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS2.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS2 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::LoadWallDataS2()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS2.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS2 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}


void GameScene::SwapEnemyDataS1() {

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
    while (getline(enemyDataS1,line))
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
            else
            {
                enemyDataS1.str("");
                enemyDataS1.clear(std::stringstream::goodbit);

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

void GameScene::SwapWallDataS1()
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
    while (getline(wallDataS1, line))
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

void GameScene::SwapEnemyDataS2() {

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
    int nextflag = 0;

    //敵のlist追加
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();


    //コマンド実行ループ
    while (getline(enemyDataS2, line))
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

            newenemy->SetPosition({ pos.x,pos.y,pos.z });

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

            newenemy->SetScale({ scale.x,scale.y,scale.z });
        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname == 1)
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
            if (mod == 0)
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

void GameScene::SwapWallDataS2()
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
    int nextflag = 0;

    //壁のlist追加
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //コマンド実行ループ
    while (getline(wallDataS2, line))
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

    if (scene==0)
    {
        if (input->TriggerKey(DIK_SPACE))
        {
            scene = 2;
            tutoscene = 0;
            transrationScene();
            spritesize = { 1280,720 };
            transfrag = true;
        }
    }

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

        //チュートリアル
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
            if (wait >= 180 && input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
            {
                tutoscene = 1;
                wait = 0;
                transfrag = true;
            }
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


        //FBX更新
        floor->Update();
        player->BulUpdate();
        backsphere->Update();
        player->BulUpdate();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetEye());

        for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }

        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Update();
        }

        //スプライト更新
        crosshair->Update();
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


        //動いていない状態で攻撃したら
        if (tutoscene==3)
        {
            if (input->PushKey(DIK_SPACE) && !input->PushKey(DIK_Q))
            {
                //フラグをtrueにする
                attack = true;
            }

            if (attack == true)
            {
                movect++;

                //敵更新
                for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }

                for (std::unique_ptr<Wall>& wall : Stage1Walls)
                {
                    wall->Update();
                }

                //プレイy－更新
                player->Setoldpos(camera->GetEye());
                player->SetoldTarget(camera->GetTarget());
                camera->CurrentUpdate();
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetTarget(camera->GetTarget());
                player->SetPosition(camera->GetEye());
                player->SetRotation(camera->GetRoatation());
                player->PlayerUpdate(camera->GetTarget());
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

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
        }

        //弾がないとき
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
       

        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            if (tutoscene==3)
            {
                //敵更新
                for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }
            }
            

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

        }

        //マウスだけ動いてる時
        if (mouseMove.lX != 0 || mouseMove.lY != 0)
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate();
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

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

        Stage1Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Stage1Enemy.size()==0)
        {
            scene = 4;//クリア
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

        //チュートリアル
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

        //FBX更新
        floor->Update();
        for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }
        for (std::unique_ptr<Wall>& wall : Stage2Walls)
        {
            wall->Update();
        }
        gunstand->Update();
        tutogun->Update();
        player->BulUpdate();
        backsphere->Update();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetEye());

        //スプライト更新
        crosshair->Update();
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

        //プレイヤーの銃のフラグ管理
        if (player->Gethave() == false)
        {
            player->Sethave(tutogun->Gethave());
        }
        if (player->Gethave() == true)
        {
            tutogun->Sethave(false);
        }

        //弾がないとき
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
            for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Stage2Walls)
            {
                wall->Update();
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

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

        ////動いていない状態で銃を投げたら
        //if (input->PushKey(DIK_Q) && !input->PushKey(DIK_SPACE))
        //{
        //    gunthrow = true;
        //}

        //if (gunthrow == true)
        //{

        //}

        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
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
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

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

        Stage2Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Stage2Enemy.size() == 0)
        {
            scene = 8;//クリア
        }
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
        player->gunUpdate(camera->GetTarget(), camera->GetEye());
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

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

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

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
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
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

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

        if (input->PushKey(DIK_SPACE))
        {
            scene = 7;
            tutoscene = 0;
            transrationScene();
        }

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
        if (input->PushKey(DIK_SPACE))
        {
            scene = 5;
            tutoscene = 3;
            transrationScene();
        }
        //backsphere->Update();

     //sprintf_s(pla, "WASD : move");

     //debugText->Print(pla, 0, 0, 1.0f);

    }

    if (scene==8)
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
        if (input->PushKey(DIK_SPACE))
        {
            scene = 7;
            tutoscene = 0;
            transrationScene();
        }
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
        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Draw(cmdList);
        }
    }

    //ステージオブジェクト
    floor->Draw(cmdList);
    if (scene == 5)
    {
        

        for (std::unique_ptr<Wall>& wall : Stage2Walls)
        {
            wall->Draw(cmdList);
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
        for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
        {
            enemy->BulDraw(cmdList);
            enemy->PartDraw(cmdList);
            enemy->Draw(cmdList);
        }
    }

    if (scene==3)
    {
        if (Stage1Walls.size() > 0)
        {
            for (std::unique_ptr<Wall>& wall : Stage1Walls)
            {
                wall->Draw(cmdList);
            }
        }

        if (Stage2Walls.size() > 0)
        {
            for (std::unique_ptr<Wall>& wall : Stage2Walls)
            {
                wall->Draw(cmdList);
            }
        }
        floor->Draw(cmdList);
    }

    if (scene == 4)
    {
        if (Stage1Walls.size() > 0)
        {
            for (std::unique_ptr<Wall>& wall : Stage1Walls)
            {
                wall->Draw(cmdList);
            }
        }

        if (Stage2Walls.size() > 0)
        {
            for (std::unique_ptr<Wall>& wall : Stage2Walls)
            {
                wall->Draw(cmdList);
            }
        }
        floor->Draw(cmdList);
    }
     
    

    //プレイヤー関連
     player->throwgunDraw(cmdList);
     player->gunDraw(cmdList);
     player->BulDraw(cmdList);
    // player->meleeDraw(cmdList);

     //スプライト描画前処理
     spriteCommon->PreDraw();

     if (scene == 2)
     {
         if (tutoscene == 0)tutomove->Draw();
         if (tutoscene == 1)tutomouse->Draw();
         if (tutoscene == 2)tutorule->Draw();
     }
     if (scene == 5)
     {
         if (tutoscene == 3)tutogunpick1->Draw();
         if (tutoscene == 4)tutogunpick2->Draw();
         if (tutoscene == 5)tutopickup->Draw();
         if (noammoflag == true)noammo->Draw();

     }

     if (scene == 3)gameover->Draw();
     if (scene == 4)clear->Draw();
    

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



}

void GameScene::transrationScene()
{
    if (scene==2)
    {
        //camera->SetEye(EyeInitialize);
        camera->SetTarget({ 0, 0, 0 });
        camera->CurrentUpdate();
        //player->Update();
        player->Sethave(true);
        /*LoadEnemyData();
        SwapEnemyData();*/

        //listの削除
       /* Stage2Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->die;
            });
        Stage2Walls.remove_if([](std::unique_ptr<Wall>& wall) {
            return wall->die;
            });*/

        LoadEnemyDataS1();
        SwapEnemyDataS1();
        LoadWallDataS1();
        SwapWallDataS1();

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
       /* player->SetPosition(respos);
        camera->SetEye(respos);*/

        

        camera->SetTarget({ 0, 0, 0 });
        camera->CurrentUpdate();

       
        LoadEnemyDataS2();
        SwapEnemyDataS2();
        LoadWallDataS2();
        SwapWallDataS2();


        //listの削除
        Stage1Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->die;
            });
        Stage1Walls.remove_if([](std::unique_ptr<Wall>& wall) {
            return wall->die;
            });

        for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }
        for (std::unique_ptr<Wall>& wall : Stage2Walls)
        {
            wall->Update();
        }

        for (int i = 0; i < 8; i++)
        {
            stage3wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage3wall[i]->Update();
        }
    }

    /*if (scene==6)
    {
        const XMFLOAT3 respos = { 0,0,0 };
        player->Sethave(false);
        player->SetPosition(respos);
        camera->SetEye(respos);

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
    }*/
    
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
