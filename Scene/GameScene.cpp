#pragma once
#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include<fstream>
#include"SceneManager.h"
#include "StageData.cpp"

using namespace DirectX;

class ClearScene;
class GameoverScene;


template<>
BaseScene* BaseScene::makeScene<GameScene>() {
    return new GameScene();
}


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
    spriteCommon->LoadTexture(5, L"Resources/tutomove.png");
    spriteCommon->LoadTexture(6, L"Resources/tutomouse.png");
    spriteCommon->LoadTexture(7, L"Resources/tutoshot.png");
    spriteCommon->LoadTexture(8, L"Resources/tutorule.png");
    spriteCommon->LoadTexture(9, L"Resources/pickuptuto.png");
    spriteCommon->LoadTexture(10, L"Resources/stage2tuto1.png");
    spriteCommon->LoadTexture(11, L"Resources/stage2tuto2.png");
    spriteCommon->LoadTexture(12, L"Resources/noammo.png");
    spriteCommon->LoadTexture(13, L"Resources/stage3tuto.png");
    spriteCommon->LoadTexture(14, L"Resources/throwguntuto.png");

    //ポストエフェクト用テクスチャの読み込み
    spriteCommon->LoadTexture(101, L"Resources/White1x1.png");

    //スプライト生成
    
    crosshair = Sprite::Create(spriteCommon, 1);
    crosshair->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    crosshair->TransferVertexBuffer();

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

    tutostage3 = Sprite::Create(spriteCommon, 13);
    tutostage3->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutostage3->TransferVertexBuffer();

    tutothrow = Sprite::Create(spriteCommon, 14);
    tutothrow->SetPosition({ WindowsApp::window_width / 2,600,0 });
    tutomove->SetSize(movesize);
    tutothrow->TransferVertexBuffer();

    noammo = Sprite::Create(spriteCommon, 12);
    noammo->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    noammo->TransferVertexBuffer();


    trans = Sprite::Create(spriteCommon, 101);
    trans->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    trans->SetSize({ Effectsize });
    trans->TransferVertexBuffer();
    
    int PFnum = 101;
    //ポストエフェクトの初期化
    transEffect = TransEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);

    collisionManager = CollisionManager::GetInstance();


    //FBX関連
    //デバイスをセット
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //カメラをセット
    FBXobj3d::SetCamera(camera);
    //FBXパイプライン生成
    FBXobj3d::CreateGraphicsPipeline();
    //file読み込み
    
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");
    modelobjgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");


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

    ////壁のスケール0.1=ワールドで10
     
    ///２面
   
    //銃台座
   /* gunstand= new Wall();
    gunstand->Initialize();
    gunstand->SetModel(model2);
    gunstand->SetPosition({ 0.0f,0.0f,10.0f });
    gunstand->SetScale({ 0.03f,0.04f,0.03f });
    gunstand->SetRotation({ 0.0f,0.0f,0.0f });
    gunstand->SetCollider(new BoxCollider(XMVECTOR{ 0.0f,0.0f,0.0f,0 }, 1.0f));
    gunstand->WallInitialize();*/

    //銃本体
    tutogun = new Wall;
    tutogun->Initialize();
    tutogun->SetPosition({ 0.0f,6.0f,10.0f });
    tutogun->SetScale({ 0.01f,0.01f,0.01f });
    tutogun->SetModel(modelobjgun);
    tutogun->SetCollider(new BoxCollider(XMVECTOR{ 4.0f,4.0f,4.0f,0 }, 1.0f));
    tutogun->objgunInitialize();

    //敵初期化
    uint32_t enemyNum = stageDatas[StageNum].enemyNum;
    for (int i = 0; i < enemyNum; i++)
    {
        std::vector<Enemy> newenemy;
        newenemy[i].Initialize();

        enemys.push_back(Enemy());
    }

    for (int i = 0; i < enemyNum; i++)
    {
        enemys[i].Initialize();
    }



    //壁
    uint32_t wallNum = stageDatas[StageNum].wallNum;

    //チュートリアル初期化
    uint32_t tutoNum = stageDatas[StageNum].tutoNum;
    for (int i = 0; i < tutoNum; i++)
    {

    }


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

void GameScene::LoadEnemyDataS3()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS3.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS3 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::LoadWallDataS3()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS3.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS3 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::LoadEnemyDataS4()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS4.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS4 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void GameScene::LoadWallDataS4()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS4.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS4 << file.rdbuf();

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
            else if (modelname == 2)
            {
                newwall->SetModel(model2);
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

void GameScene::SwapEnemyDataS3() {

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
    while (getline(enemyDataS3, line))
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
            if (stage == 3)
            {
                Stage3Enemy.push_back(std::move(newenemy));
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
    }
}

void GameScene::SwapWallDataS3()
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
    while (getline(wallDataS3, line))
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
            else if (modelname == 2)
            {
                newwall->SetModel(model2);
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
            if (stage == 3)
            {
                newwall->WallInitialize();
                Stage3Walls.push_back(std::move(newwall));
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

void GameScene::SwapEnemyDataS4() {

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
    while (getline(enemyDataS4, line))
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
            if (stage == 4)
            {
                Stage4Enemy.push_back(std::move(newenemy));
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
    }
}

void GameScene::SwapWallDataS4()
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
    while (getline(wallDataS4, line))
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
            if (stage == 4)
            {
                newwall->WallInitialize();
                Stage4Walls.push_back(std::move(newwall));
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

    // マウスの入力を取得
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);


    if (transscene==false)
    {
        transcount += 1.0f;

        if (transcount >= 120.0f)
        {
            transrationScene();
            transcount = 0.0f;
            transscene = true;
        }
    }


    //ゲーム本編
    //ステージ１
    if (playscene == 2 && transscene==true)
    {

        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 1)
        {
            camera->CurrentUpdate(player->GetVelocity());
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
            if (wait >= 60 && input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
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
            if (wait >= 60)
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
        player->PartUpdate();

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

        noammo->Update();


        //動いていない状態で攻撃したら
        if (tutoscene==3)
        {
            if (input->PushclickLeft() && !input->PushKey(DIK_Q))
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
                camera->CurrentUpdate(player->GetVelocity());
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

        if (attack == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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
        if (input->PushclickRight() && !input->PushclickLeft())
        {
            gunthrow = true;
        }

        if (gunthrow == true)
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
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
            tutogun->Update();

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                gunthrow = false;
                movect = 0;
            }
        }

        timecount++;

        //弾がないとき
        if (magazin == 0 && have == true && input->PushclickLeft())
        {
            noammoflag = true;
        }

        if (noammoflag == true)
        {
            spritesize.x -= 2.0f;
            spritesize.y -= 2.0f;
            wait++;
        }

        if (noammoflag == true && wait >= 60)
        {
            spritesize = { 1280,720 };
            noammoflag = false;
            wait = 0;
        }
       
        timecount++;

        //壁に当たる前の座標
        camera->SetWallEye(camera->GetEye());
        camera->SetWallTarget(camera->GetTarget());


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
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

        }
        else if(timecount>=30)
        {
            if (tutoscene == 3)
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
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

            timecount = 0;

        }

        //マウスだけ動いてる時
        if (mouseMove.lX != 0 || mouseMove.lY != 0)
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate(player->GetVelocity());
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

            }
        }

        player->Setwallflag(false);

        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        camera->Setwallflag(player->Getwallhit());

        if (player->Getwallhit() == true)
        {
            camera->Setwallflag(player->Getwallhit());

            /* for (int i = 0; i < 60; i++)
             {
                 collisionManager->CheckAllCollisions();
                 if (player->Getwallhit() == false)
                 {
                     break;
                 }
                 player->QueryWall();
                 camera->SetEye(player->GetPos());
                 camera->SetTarget(player->GetTarget());
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
             }*/
            camera->SetEye(camera->GetWallEye());
            camera->SetTarget(camera->GetWallTarget());


        }



        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<GameoverScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }

        //パーティクル出し終わったらリスト削除
        Stage1Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Stage1Enemy.size() == 1)
        {
            for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
            {
                enemy->LastUpdate();
            }
        }

        //敵全員倒したらクリア
        if (Stage1Enemy.size()==0)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<ClearScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);

        }

    }

    //ステージ２
    if (playscene == 5 && transscene == true)
    {
        
        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 0)
        {
            camera->CurrentUpdate(player->GetVelocity());
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
            if (wait >= 60)
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
            if (wait >= 60)
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
            if (wait >= 60 && input->PushclickLeft())
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
        //gunstand->Update();
        tutogun->Update();
        player->BulUpdate();
        backsphere->Update();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetEye());
        player->PartUpdate();

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
        if (magazin == 0 && have == true && input->PushclickLeft())
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
        if (input->PushclickLeft() && !input->PushKey(DIK_Q))
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
            camera->CurrentUpdate(player->GetVelocity());
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
        if (input->PushclickRight() && !input->PushclickLeft())
        {
            gunthrow = true;
        }
        if (gunthrow == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Stage3Walls)
            {
                wall->Update();
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
            tutogun->Update();

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                gunthrow = false;
                movect = 0;
            }
        }

        timecount++;

        //壁に当たる前の座標
        camera->SetWallEye(camera->GetEye());
        camera->SetWallTarget(camera->GetTarget());

      
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
            camera->CurrentUpdate(player->GetVelocity());
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
        else if (timecount>=60)
        {
            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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

            timecount = 0;

        }


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//マウスだけ動いてる時
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate(player->GetVelocity());
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

            }
        }


        player->Setwallflag(false);

        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        camera->Setwallflag(player->Getwallhit());

        if (player->Getwallhit() == true)
        {
            camera->Setwallflag(player->Getwallhit());

            /* for (int i = 0; i < 60; i++)
             {
                 collisionManager->CheckAllCollisions();
                 if (player->Getwallhit() == false)
                 {
                     break;
                 }
                 player->QueryWall();
                 camera->SetEye(player->GetPos());
                 camera->SetTarget(player->GetTarget());
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
             }*/
            camera->SetEye(camera->GetWallEye());
            camera->SetTarget(camera->GetWallTarget());


        }


        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<GameoverScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }

        Stage2Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Stage2Enemy.size() == 1)
        {
            for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
            {
                enemy->LastUpdate();
            }
        }

        //敵が全員いなくなったら
        if (Stage2Enemy.size() == 0)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<ClearScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }
    }

    //ステージ3
    if (playscene == 6 && transscene == true)
    {
       
        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 0)
        {
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 1;
        }

        //FBX更新
        floor->Update();
        for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }
        for (std::unique_ptr<Wall>& wall : Stage3Walls)
        {
            wall->Update();
        }
        player->BulUpdate();
        backsphere->Update();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetEye());
        tutogun->Update();
        player->PartUpdate();

        //スプライト更新
        crosshair->Update();

        noammo->TransferVertexBuffer();
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

        if (tutoscene == 6)
        {
            if (spritesize.x >= 1280)
            {
                transfrag = true;
            }

            if (transfrag == true)
            {
                spritesize.x -= 2.0f;
                spritesize.y -= 2.0f;
            }
            wait++;
            if (wait >= 60)
            {
                tutoscene = 7;
                spritesize = { 1280,720 };
                transfrag = true;
                wait = 0;
            }
        }

        if (tutoscene == 7)
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
            if (input->PushclickRight())
            {
                tutoscene = 8;
                wait = 0;

            }
        }

        tutothrow->SetSize(movesize);
        tutostage3->SetSize(spritesize);

        tutothrow->TransferVertexBuffer();
        tutostage3->TransferVertexBuffer();

        tutothrow->Update();
        tutostage3->Update();


        //動いていない状態で攻撃したら
        if (input->PushclickLeft() && !input->PushKey(DIK_Q))
        {
            //フラグをtrueにする
            attack = true;
        }

        if (attack == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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
        if (input-> PushclickRight() && !input->PushclickLeft())
        {
            gunthrow = true;
        }

        if (gunthrow == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Stage3Walls)
            {
                wall->Update();
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
            tutogun->Update();

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                gunthrow = false;
                movect = 0;
            }
        }

        //弾がないとき
        if (magazin == 0 && have == true && input->PushclickLeft())
        {
            noammoflag = true;
        }

        if (noammoflag == true)
        {
            spritesize.x -= 2.0f;
            spritesize.y -= 2.0f;
            wait++;
        }

        if (noammoflag == true && wait >= 60)
        {
            spritesize = { 1280,720 };
            noammoflag = false;
            wait = 0;
        }

        timecount++;

        //壁に当たる前の座標
        camera->SetWallEye(camera->GetEye());
        camera->SetWallTarget(camera->GetTarget());

        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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
        else if (timecount >= 30)
        {
            for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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

            timecount = 0;
        }

        if (player->Gethave() == true)
        {
            tutogun->SetPosition({ 0,100.0f,0 });
        }
        else
        {
            tutogun->SetPosition({ 0.0f,2.0f,20.0f });
        }


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//マウスだけ動いてる時
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                camera->CurrentUpdate(player->GetVelocity());
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetPosition(camera->GetEye());
                player->SetTarget(camera->GetTarget());
                player->UpdateWorld();
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

            }
        }

        player->Setwallflag(false);

        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        camera->Setwallflag(player->Getwallhit());

        if (player->Getwallhit() == true)
        {
            camera->Setwallflag(player->Getwallhit());

            /* for (int i = 0; i < 60; i++)
             {
                 collisionManager->CheckAllCollisions();
                 if (player->Getwallhit() == false)
                 {
                     break;
                 }
                 player->QueryWall();
                 camera->SetEye(player->GetPos());
                 camera->SetTarget(player->GetTarget());
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
             }*/
            camera->SetEye(camera->GetWallEye());
            camera->SetTarget(camera->GetWallTarget());


        }


        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<GameoverScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }

        //パーティクル出し終わったらリスト削除
        Stage3Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Stage3Enemy.size() == 1)
        {
            for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
            {
                enemy->LastUpdate();
            }
        }

        //敵全員倒したらクリア
        if (Stage3Enemy.size() == 0)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<ClearScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }

    }

    //ステージ4
    if (playscene==7 && transscene == true)
    {
        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 0)
        {
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 1;
        }

        //FBX更新
        floor->Update();
        for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }
        for (std::unique_ptr<Wall>& wall : Stage4Walls)
        {
            wall->Update();
        }
        player->BulUpdate();
        backsphere->Update();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetEye());
        tutogun->Update();
        player->PartUpdate();

        //スプライト更新
        crosshair->Update();
        noammo->TransferVertexBuffer();
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

        //動いていない状態で攻撃したら、攻撃フラグを立てる
        if (input->PushclickLeft() && !input->PushKey(DIK_Q))
        {
            //フラグをtrueにする
            attack = true;
        }
        //フラグが立っていたら更新
        if (attack == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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

        //動いていない状態で銃を投げたら、フラグを立てる
        if (input->PushclickRight() && !input->PushclickLeft())
        {
            gunthrow = true;
        }
        //フラグがたっていたら更新
        if (gunthrow == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Stage4Walls)
            {
                wall->Update();
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
            tutogun->Update();

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                gunthrow = false;
                movect = 0;
            }
        }

        if (noammoflag == true)
        {
            spritesize.x -= 2.0f;
            spritesize.y -= 2.0f;
            wait++;
        }

        if (noammoflag == true && wait >= 60)
        {
            spritesize = { 1280,720 };
            noammoflag = false;
            wait = 0;
        }

        timecount++;
        //壁に当たる前の座標
        camera->SetWallEye(camera->GetEye());
        camera->SetWallTarget(camera->GetTarget());

        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            player->PlayerUpdate(camera->GetTarget());
            if (wallcol == false)
            {
                camera->CurrentUpdate(player->GetVelocity());
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            }
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());

            /*camera->SetEye(player->GetPos());
            camera->SetTarget(player->GetTarget());*/
            
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

        }
        else if (timecount >= 30)
        {
            for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy－更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
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

            timecount = 0;
        }

        if (player->Gethave() == true)
        {
            tutogun->SetPosition({ 0,100.0f,0 });
        }
        else
        {
            tutogun->SetPosition({ 0.0f,2.0f,20.0f });
        }


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//マウスだけ動いてる時
        {
            if (!input->PushKey(DIK_W) && !input->PushKey(DIK_A) && !input->PushKey(DIK_S) && !input->PushKey(DIK_D))
            {
                if (wallcol==false)
                {
                    camera->CurrentUpdate(player->GetVelocity());
                    player->SetPosition(camera->GetEye());
                    player->SetTarget(camera->GetTarget());
                    player->UpdateWorld();
                    player->gunUpdate(camera->GetTarget(), camera->GetEye());
                }
            }
        }


        player->Setwallflag(false);

        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

        camera->Setwallflag(player->Getwallhit());

        if (player->Getwallhit() == true)
        {
            camera->Setwallflag(player->Getwallhit());

            /* for (int i = 0; i < 60; i++)
             {
                 collisionManager->CheckAllCollisions();
                 if (player->Getwallhit() == false)
                 {
                     break;
                 }
                 player->QueryWall();
                 camera->SetEye(player->GetPos());
                 camera->SetTarget(player->GetTarget());
                 camera->Update(WindowsApp::window_width, WindowsApp::window_height);
             }*/
            camera->SetEye(camera->GetWallEye());
            camera->SetTarget(camera->GetWallTarget());


        }



        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == 1)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<GameoverScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }


        //パーティクル出し終わったらリスト削除
        Stage4Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Stage4Enemy.size() == 1)
        {
            for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
            {
                enemy->LastUpdate();
            }
        }

        //敵全員倒したらクリア
        if (Stage4Enemy.size() == 0)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<ClearScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }
    }

}

void GameScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

    //FBX描画
    if (playscene==2)
    {
        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Draw(cmdList);
        }
    }

    //ステージオブジェクト
    floor->Draw(cmdList);

    if (playscene == 5)
    {
        
        for (std::unique_ptr<Wall>& wall : Stage2Walls)
        {
            wall->Draw(cmdList);
        }

        tutogun->Draw(cmdList);
    }

    if (playscene==6)
    {
        for (std::unique_ptr<Wall>& wall : Stage3Walls)
        {
            wall->Draw(cmdList);
        }

        tutogun->Draw(cmdList);
    }

    if (playscene == 7)
    {
        for (std::unique_ptr<Wall>& wall : Stage4Walls)
        {
            wall->Draw(cmdList);
        }

        tutogun->Draw(cmdList);
    }
    

    //敵関連
    if (playscene==2)
    {
        for (std::unique_ptr<Enemy>& enemy : Stage1Enemy)
        {
            enemy->BulDraw(cmdList);
            enemy->PartDraw(cmdList);
            enemy->Draw(cmdList);
        }
        
    }

    if (playscene==5)
    {
        for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
        {
            enemy->BulDraw(cmdList);
            enemy->PartDraw(cmdList);
            enemy->Draw(cmdList);
        }
    }

    if (playscene == 6)
    {
        for (std::unique_ptr<Enemy>& enemy : Stage3Enemy)
        {
            enemy->BulDraw(cmdList);
            enemy->PartDraw(cmdList);
            enemy->Draw(cmdList);
        }
    }

    if (playscene == 7)
    {
        for (std::unique_ptr<Enemy>& enemy : Stage4Enemy)
        {
            enemy->BulDraw(cmdList);
            enemy->PartDraw(cmdList);
            enemy->Draw(cmdList);
        }
    }

    

    //プレイヤー関連
    player->Draw(cmdList);

     //スプライト描画前処理
     spriteCommon->PreDraw();

     //シーン切り替え処理
     if (transscene == false)
     {
         transEffect->Draw(cmdList);
     }



     if (playscene == 2)
     {
         if (tutoscene == 0)tutomove->Draw();
         if (tutoscene == 1)tutomouse->Draw();
         if (tutoscene == 2)tutorule->Draw();
         if (noammoflag == true)noammo->Draw();
     }
     if (playscene == 5)
     {
         if (tutoscene == 3)tutogunpick1->Draw();
         if (tutoscene == 4)tutogunpick2->Draw();
         if (tutoscene == 5)tutopickup->Draw();
         if (noammoflag == true)noammo->Draw();
     }

     if (playscene == 6)
     {
         if (tutoscene == 6)tutostage3->Draw();
         if (tutoscene == 7)tutothrow->Draw();

         if (noammoflag == true)noammo->Draw();
     }

     if (playscene == 7)
     {
         if (noammoflag == true)noammo->Draw();
     }


     if (playscene != 0)
     {
         crosshair->Draw();
     }
    

    // デバッグテキスト描画
    //debugText->DrawAll();
}


void GameScene::transrationScene()
{
    //ステージ1
    if (playscene==2)
    {

        const XMFLOAT3 respos = { 0,5,0 };

        camera->SetTarget({ 0, 5, 0 });
        camera->SetEye(respos);
        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
        camera->CurrentUpdate(player->GetVelocity());

        player->Sethave(true);
        player->SetPosition(camera->GetEye());
        player->PlayerUpdate(camera->GetTarget());

        tutoscene = 0;

        LoadEnemyDataS1();
        SwapEnemyDataS1();
        LoadWallDataS1();
        SwapWallDataS1();

    }

    //ステージ2
    if (playscene==5)
    {
        const XMFLOAT3 respos={0,5,0};
       
        camera->SetTarget({ 0, 5, 0 });
        camera->SetEye(respos);
        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
        camera->CurrentUpdate(player->GetVelocity());

        player->Sethave(false);
        player->SetPosition(camera->GetEye());
        player->PlayerUpdate(camera->GetTarget());

        tutoscene = 3;
       
        LoadEnemyDataS2();
        SwapEnemyDataS2();
        LoadWallDataS2();
        SwapWallDataS2();

        magazin = 5;
        player->SetMagazin(magazin);

        ////listの削除
        //Stage1Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
        //    return enemy->die;
        //    });
        //Stage1Walls.remove_if([](std::unique_ptr<Wall>& wall) {
        //    return wall->die;
        //    });

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

    }

    //ステージ3
    if (playscene==6)
    {
        const XMFLOAT3 respos = { 0,5,0 };
        camera->SetTarget({ 0, 5, 0 });
        camera->SetEye(respos);
        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
        camera->CurrentUpdate(player->GetVelocity());

        magazin = 0;
        player->SetMagazin(magazin);
        player->Sethave(true);
        player->SetPosition(camera->GetEye());
        player->PlayerUpdate(camera->GetTarget());

        tutoscene = 6;

        LoadEnemyDataS3();
        SwapEnemyDataS3();
       LoadWallDataS3();
        SwapWallDataS3();
     
        tutogun->SetPosition({ 0.0f,0.0f,20.0f });
        tutogun->Update();

    }

    //ステージ4
    if (playscene == 7)
    {
        const XMFLOAT3 respos = { 0,5,0 };
        player->Sethave(false);
        camera->SetTarget({ 0, 5, 0 });
        camera->SetEye(respos);
        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
        camera->CurrentUpdate(player->GetVelocity());

        magazin = 5;
        player->SetMagazin(magazin);
        player->SetPosition(camera->GetEye());
        player->PlayerUpdate(camera->GetTarget());
        player->Sethave(true);

        LoadEnemyDataS4();
        SwapEnemyDataS4();
        LoadWallDataS4();
        SwapWallDataS4();


        ////listの削除
        //Stage3Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
        //    return enemy->die;
        //    });
        //Stage3Walls.remove_if([](std::unique_ptr<Wall>& wall) {
        //    return wall->die;
        //    });

        tutogun->SetPosition({ 0.0f,0.0f,30.0f });
        tutogun->Update();

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


    

}
