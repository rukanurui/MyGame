#pragma once
#include "GameScene.h"
#include <cassert>
#include <iomanip>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include"SceneManager.h"


using namespace DirectX;

int GameScene::tutonum = 0;
int GameScene::enemyNum = 0;
int  GameScene::wallNum = 0;

class ClearScene;
class GameoverScene;


template<>
BaseScene* BaseScene::makeScene<GameScene>() {
    return new GameScene();
}


void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //ポインタ置き場

    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->Windows = windows;
    stagedata = new StageData;

    //カメラ生成
    camera = new Camera(this->input, this->Windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);


#pragma region 描画初期化処理


    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    // スプライト共通テクスチャ読み込み
    spriteCommon->LoadTexture(1, L"Resources/1432.png");
    spriteCommon->LoadTexture(5, L"Resources/stage1tuto/tutomove.png");
    spriteCommon->LoadTexture(6, L"Resources/stage1tuto/tutomouse.png");
    spriteCommon->LoadTexture(7, L"Resources/stage1tuto/tutoshot.png");
    spriteCommon->LoadTexture(8, L"Resources/stage1tuto/tutorule.png");
    spriteCommon->LoadTexture(9, L"Resources/pickuptuto.png");
    spriteCommon->LoadTexture(10, L"Resources/stage2tuto1.png");
    spriteCommon->LoadTexture(11, L"Resources/stage2tuto2.png");
    spriteCommon->LoadTexture(12, L"Resources/noammo.png");
    spriteCommon->LoadTexture(13, L"Resources/stage3tuto.png");
    spriteCommon->LoadTexture(14, L"Resources/throwguntuto.png");
    spriteCommon->LoadTexture(15, L"Resources/stage1tuto/tutotime.png");
    spriteCommon->LoadTexture(16, L"Resources/play.png");
    spriteCommon->LoadTexture(17, L"Resources/stop.png");
    spriteCommon->LoadTexture(18, L"Resources/ammo.png");
    spriteCommon->LoadTexture(19, L"Resources/ammoone.png");
    spriteCommon->LoadTexture(20, L"Resources/stage1tuto/Wmovetuto.png");
    spriteCommon->LoadTexture(21, L"Resources/stage1tuto/lefttuto.png");


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

    tutotime = Sprite::Create(spriteCommon, 15);
    tutotime->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    tutotime->TransferVertexBuffer();

    play = Sprite::Create(spriteCommon, 16);
    play->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    play->TransferVertexBuffer();

    stop = Sprite::Create(spriteCommon, 17);
    stop->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    stop->TransferVertexBuffer();

    ammo = Sprite::Create(spriteCommon, 18);
    ammo->SetPosition({ 1000,100,0 });
    ammo->SetSize(ammosize);
    ammo->TransferVertexBuffer();

    for (int i = 0; i < 5; i++)
    {
        ammoone[i] = Sprite::Create(spriteCommon, 19);
        ammoone[i]->SetPosition({ 1080.0f+i*15.0f,100.0f,0 });
        ammoone[i]->SetSize(ammoonesize);
        ammoone[i]->TransferVertexBuffer();
    }

    Wtuto = Sprite::Create(spriteCommon, 20);
    Wtuto->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    Wtuto->TransferVertexBuffer();

    lefttuto = Sprite::Create(spriteCommon, 21);
    lefttuto->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    lefttuto->TransferVertexBuffer();
    

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
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelobjgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelenemy = FbxLoader::GetInstance()->LoadModelFromFile("enemy");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");


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

    //ステージデータ読み取り
    stagedata->InsertData(playscene, tutonum, enemyNum, wallNum,
        enemypos, enemyscale, enemymodelname, enemyr, enemymod,
        wallpos, wallscale, wallrotation, wallmodelname, wallr);

    player->setscene(playscene);
    player->settuto(tutonum);
    player->setnowtuto(tutocount);
    camera->Setscene(playscene);
    camera->Settuto(tutonum);
    camera->Setnowtuto(tutocount);



    //敵の生成
    for (int i = 0; i < enemyNum; i++)
    {
        std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
        newenemy->Initialize();
        newenemy->SetPosition({ enemypos[i].x,enemypos[i].y,enemypos[i].z });
        newenemy->SetScale({ enemyscale[i].x,enemyscale[i].y,enemyscale[i].z });


        if (enemymodelname[i] == 1)
        {
            newenemy->SetModel(modelenemy);
        }
        newenemy->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, enemyr[i]));
        if (enemymod[i] == 0)
        {
            newenemy->EnemyInitialize(TRUE,camera, dxcommon);
        }
        else if (enemymod[i] == 1)
        {
            newenemy->EnemyInitialize(FALSE,camera, dxcommon);
        }
        Enemys.push_back(std::move(newenemy));
    }

    for (int i = 0; i < wallNum; i++)
    {
        std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
        newwall->Initialize();
        newwall->SetPosition({ wallpos[i].x,wallpos[i].y,wallpos[i].z });
        newwall->SetScale({ wallscale[i].x,wallscale[i].y,wallscale[i].z });
        newwall->SetRotation({ wallrotation[i].x,wallrotation[i].y,wallrotation[i].z });
        if (wallmodelname[i] == 1)
        {
            newwall->SetModel(modelwall);
        }
        else if (wallmodelname[i] == 2)
        {
            newwall->SetModel(modelenemy);
        }
        newwall->SetCollider(new BoxCollider(XMVECTOR{ wallr[i].x,wallr[i].y,wallr[i].z,0 }, 1.0f));
        newwall->WallInitialize();
        Walls.push_back(std::move(newwall));
    }

    //落ちている銃
    if (playscene == 2)
    {
        tutogun = new Wall;
        tutogun->Initialize();
        tutogun->SetPosition({ 0.0f,1.0f,8.0f });
        tutogun->SetScale({ 0.01f,0.01f,0.01f });
        tutogun->SetModel(modelobjgun);
        tutogun->SetCollider(new BoxCollider(XMVECTOR{ 3.0f,2.0f,3.0f,0 }, 1.0f));
        tutogun->objgunInitialize();
    }

    if (playscene == 3)
    {
        tutogun = new Wall;
        tutogun->Initialize();
        tutogun->SetPosition({ 0.0f,0.0f,20.0f });
        tutogun->SetScale({ 0.01f,0.01f,0.01f });
        tutogun->SetModel(modelobjgun);
        tutogun->SetCollider(new BoxCollider(XMVECTOR{ 3.0f,2.0f,3.0f,0 }, 1.0f));
        tutogun->objgunInitialize();
    }
    

    int counter = 0; // アニメーションの経過時間カウンター(アニメーションするfbxの時のみ使用)

}


void GameScene::Update()
{

    // マウスの入力を取得
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);

    //画面遷移処理
    if (transscene == false)
    {
        transcount += 1.0f;

        if (transcount >= 120.0f)
        {
            transcount = 0.0f;
            transscene = true;
            if (playscene==1)
            {
                const XMFLOAT3 respos = { 0,5,0 };

                camera->SetTarget(respos);
                //camera->SetEye(respos);
                
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                //camera->CurrentUpdate(player->GetVelocity());

                player->Sethave(true);
                player->SetPosition(camera->GetEye());
                player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
                magazin = 5;
                player->SetMagazin(magazin);

            }
            else if (playscene == 2)
            {
                const XMFLOAT3 respos = { 0,5,0 };

                camera->SetTarget({respos});
                //camera->SetEye(respos);
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                //camera->CurrentUpdate(player->GetVelocity());

                player->Sethave(false);
                player->SetPosition(camera->GetEye());
                player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
                magazin = 0;

            }
            else if (playscene == 3)
            {
                const XMFLOAT3 respos = { 0,5,0 };
                camera->SetTarget(respos);
                camera->SetEye(respos);
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                camera->CurrentUpdate(player->GetVelocity());

                magazin = 0;
                player->SetMagazin(magazin);
                player->Sethave(true);
                player->SetPosition(camera->GetEye());
                player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
            }
        }
    }


    //ゲーム本編
    if (transscene == true)
    {
        //描画のためにカメラの更新処理を一回呼び出す
        if (firstfrag == 1)
        {
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 0;
        }

        //チュートリアル
        if (playscene == 1)
        {
            if (tutonum >= tutocount)
            {
                if (tutocount == 0)
                {
                    tutomove->SetSize(movesize);
                    tutomove->TransferVertexBuffer();
                    tutomove->Update();

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
                        movesize.x -= 1.0f;
                        movesize.y -= 1.0f;
                    }
                    else
                    {
                        movesize.x += 0.4f;
                        movesize.y += 0.4f;
                    }

                    wait++;
                    if (player->GetPosX() >= 15.0f)
                    {
                        tutocount++;
                        movesize.x = 800;
                        wait = 0;
                        transfrag = true;
                    }
                }

                if (tutocount == 1)
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
                        spritesize.x -= 4.0f;
                        spritesize.y -= 4.0f;
                    }
                    else
                    {
                        spritesize.x += 4.0f;
                        spritesize.y += 4.0f;
                    }
                    wait++;
                    if (wait>=120)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        transfrag = true;
                        wait = 0;
                    }
                }

                if (tutocount == 2)
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
                        movesize.x -= 1.0f;
                        movesize.y -= 1.0f;
                    }
                    else
                    {
                        movesize.x += 0.4f;
                        movesize.y += 0.4f;
                    }
                    wait++;
                    if (camera->Getnowtuto() == 3)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        transfrag = true;
                        wait = 0;
                    }
                }

                if (tutocount == 3)
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
                        movesize.x -= 0.6f;
                        movesize.y -= 0.6f;
                    }
                    else
                    {
                        movesize.x += 0.2f;
                        movesize.y += 0.2f;
                    }
                    wait++;
                    if (input->PushclickLeft())
                    {
                        attack = true;
                        tutocount++;
                        spritesize = { 1280,720 };
                        wait = 0;
                    }
                }

                if (tutocount == 4)
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
                        spritesize.x -= 4.0f;
                        spritesize.y -= 4.0f;
                    }
                    else
                    {
                        spritesize.x += 4.0f;
                        spritesize.y += 4.0f;
                    }

                    wait++;
                    if (wait>=120)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        wait = 0;
                        transfrag = true;
                    }
                }

                if (tutocount == 5)
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
                        spritesize.x -= 4.0f;
                        spritesize.y -= 4.0f;
                    }
                    else
                    {
                        spritesize.x += 4.0f;
                        spritesize.y += 4.0f;
                    }

                    wait++;
                    if (wait >= 120)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        wait = 0;
                        transfrag = true;
                    }
                }
            }

            Wtuto->SetSize(movesize);
            lefttuto->SetSize(movesize);;
            tutomouse->SetSize(spritesize);
            tutoshot->SetSize(movesize);
            tutorule->SetSize(spritesize);
            tutotime->SetSize(spritesize);

            Wtuto->TransferVertexBuffer();
            lefttuto->TransferVertexBuffer();
            tutomouse->TransferVertexBuffer();
            tutotime->TransferVertexBuffer();
            tutoshot->TransferVertexBuffer();
            tutorule->TransferVertexBuffer();

            Wtuto->Update();
            lefttuto->Update();
            tutomouse->Update();
            tutotime->Update();
            tutoshot->Update();
            tutorule->Update();

            //カメラとplayerに現在のチュートリアル渡す
            player->setnowtuto(tutocount);
            camera->Setnowtuto(tutocount);

        }

        //チュートリアル
        if (playscene == 2)
        {
            if (tutonum >= tutocount)
            {
                if (tutocount == 0)
                {
                    if (spritesize.x >= 1280)
                    {
                        transfrag = true;
                    }

                    if (transfrag == true)
                    {
                        spritesize.x -= 4.0f;
                        spritesize.y -= 4.0f;
                    }

                    wait++;
                    if (wait >= 60)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        wait = 0;
                        transfrag = true;
                    }
                }

                if (tutocount == 1)
                {
                    if (spritesize.x >= 1280)
                    {
                        transfrag = true;
                    }

                    if (transfrag == true)
                    {
                        spritesize.x -= 4.0f;
                        spritesize.y -= 4.0f;
                    }
                    wait++;
                    if (wait >= 60)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        transfrag = true;
                        wait = 0;
                    }
                }

                if (tutocount == 2)
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
                        movesize.x -= 0.6f;
                        movesize.y -= 0.6f;
                    }
                    else
                    {
                        movesize.x += 0.6f;
                        movesize.y += 0.6f;
                    }

                    wait++;
                    if (input->TriggerKey(DIK_F))
                    {
                        tutocount++;
                        wait = 0;

                    }
                }
            }

            tutopickup->SetSize(movesize);
            tutogunpick1->SetSize(spritesize);
            tutogunpick2->SetSize(spritesize);

            tutopickup->TransferVertexBuffer();
            tutogunpick1->TransferVertexBuffer();
            tutogunpick2->TransferVertexBuffer();

            tutopickup->Update();
            tutogunpick1->Update();
            tutogunpick2->Update();

            //カメラとplayerに現在のチュートリアル渡す
            player->setnowtuto(tutocount);
            camera->Setnowtuto(tutocount);

        }

        //チュートリアル
        if (playscene == 3)
        {
            if (tutonum >= tutocount)
            {
                if (tutocount == 0)
                {
                    if (spritesize.x >= 1280)
                    {
                        transfrag = true;
                    }

                    if (transfrag == true)
                    {
                        spritesize.x -= 4.0f;
                        spritesize.y -= 4.0f;
                    }
                    wait++;
                    if (wait >= 60)
                    {
                        tutocount++;
                        spritesize = { 1280,720 };
                        transfrag = true;
                        wait = 0;
                    }
                }

                if (tutocount == 1)
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
                        movesize.x -= 0.6f;
                        movesize.y -= 0.6f;
                    }
                    else
                    {
                        movesize.x += 0.6f;
                        movesize.y += 0.6f;
                    }

                    wait++;
                    if (input->PushclickRight())
                    {
                        tutocount++;
                        wait = 0;
                    }
                }

                tutostage3->SetSize(spritesize);

            }

            tutothrow->SetSize(movesize);
            tutostage3->SetSize(spritesize);

            tutothrow->TransferVertexBuffer();
            tutostage3->TransferVertexBuffer();

            tutothrow->Update();
            tutostage3->Update();

            //カメラとplayerに現在のチュートリアル渡す
            player->setnowtuto(tutocount);
            camera->Setnowtuto(tutocount);

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
        player->BullisticUpdate();
        camera->Update(WindowsApp::window_width, WindowsApp::window_height);

        for (std::unique_ptr<Enemy>& enemy : Enemys)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->BullisticUpdate();
            enemy->Update();
        }

        for (std::unique_ptr<Wall>& wall : Walls)
        {
            wall->Update();
        }

        //スプライト更新
        crosshair->Update();
        noammo->Update();
        ammo->Update();
        play->Update();
        stop->Update();

        
        for (int i = 0; i < 5; i++)
        {
            ammoone[i]->Update();
        }

        if (playscene >=2) //プレイヤーの銃のフラグ管理)
        {
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
        }
        
        if (playscene >= 2)
        {
            if (!input->PushclickLeft() && !input->PushKey(DIK_Q) && input->PushKey(DIK_F))
            {
                //フラグをtrueにする
                gunpick = true;
            }

            if (gunpick==true)
            {
                movect++;
            }
        }

        if (gunpick == true)
        {
            movect++;

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

            if (playscene >= 2)
            {
                tutogun->Update();
            }

            //残弾数の取得
            magazin = player->Getmagazin();
            //銃を持っているか
            have = player->Gethave();

            if (movect >= 15)
            {
                gunpick = false;
                movect = 0;
            }
        }
        
        //動いていない状態で攻撃したら
        if (tutonum <= tutocount)
        {
            if (input->PushclickLeft() && !input->PushclickRight())
            {
                //フラグをtrueにする
                attack = true;
            }

        }

        if (tutonum <= tutocount)
        {
            if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
            {
                playflag = true;
            }
            else
            {
                playflag = false;
            }
        }

        if (attack == true)
        {
            movect++;

            //敵更新
            for (std::unique_ptr<Enemy>& enemy : Enemys)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
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
            for (std::unique_ptr<Enemy>& enemy : Enemys)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Walls)
            {
                wall->Update();
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());
            


            if (playscene>=2)
            {
                tutogun->Update();
            }
            

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
            spritesize.x -= 3.0f;
            spritesize.y -= 3.0f;
            wait++;
        }

        if (noammoflag == true && wait >= 60)
        {
            spritesize = { 1280,720 };
            noammoflag = false;
            wait = 0;
        }

        noammo->SetSize(spritesize);
        noammo->TransferVertexBuffer();
        noammo->Update();

        timecount++;

        //壁に当たる前の座標
        camera->SetWallEye(camera->GetEye());
        camera->SetWallTarget(camera->GetTarget());


        //自分が動いていたら更新処理
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            if (tutonum <= tutocount)
            {
                //敵更新
                for (std::unique_ptr<Enemy>& enemy : Enemys)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            if (gunpick==false && attack==false && gunthrow == false)
            {
                camera->CurrentUpdate(player->GetVelocity());
            }
            
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

        }
        else if (timecount >= 30)
        {
            if (tutoscene == 3)
            {
                //敵更新
                for (std::unique_ptr<Enemy>& enemy : Enemys)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }
            }

            //プレイy−更新
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget(), camera->GetEye());
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

        //壁と当たっているかのフラグを下げる
        player->Setwallhit(false);
        camera->Setwallflag(player->Getwallhit());

        //すべての衝突をチェック
        collisionManager->CheckAllCollisions();

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

            camera->CurrentUpdate(player->GetVelocity());
            

        }

        //プレイヤーに敵が当たったらシーン遷移
        if (player->Gethit() == true)
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<GameoverScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }

        //パーティクル出し終わったらリスト削除
        Enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {
            return enemy->getdeath();
            });

        if (Enemys.size() == 1)
        {
            for (std::unique_ptr<Enemy>& enemy : Enemys)
            {
                enemy->LastUpdate();
            }
        }

        //敵全員倒したらクリア
        if (Enemys.size() == 0)
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

    for (std::unique_ptr<Wall>& wall : Walls)
    {
        wall->Draw(cmdList);
    }

    //ステージオブジェクト
    floor->Draw(cmdList);

    if (playscene==2)
    {
        tutogun->Draw(cmdList);
    }

    if (playscene == 3)
    {
        tutogun->Draw(cmdList);
    }

    //敵関連
    for (std::unique_ptr<Enemy>& enemy : Enemys)
    {
        enemy->BulDraw(cmdList);
        enemy->PartDraw(cmdList);
        enemy->BullisticDraw(cmdList);
        enemy->Draw(cmdList);
    }
    

    //プレイヤー関連
    player->Draw(cmdList);

     //スプライト描画前処理
     spriteCommon->PreDraw();

     ammo->Draw();

     for (int i = 0; i < magazin; i++)
     {
         ammoone[i]->Draw();
     }

     //シーン切り替え処理
     if (transscene == false)
     {
         transEffect->Draw(cmdList);
     }

     if (playscene == 1)
     {
         if (tutocount == 0)Wtuto->Draw();
        
         if (tutocount == 1)tutomouse->Draw();
       
         if (tutocount == 2)lefttuto->Draw();
         if (tutocount == 3)tutoshot->Draw();
         if (tutocount == 4)tutotime->Draw();
         if (tutocount == 5)tutorule->Draw();

         if (tutocount>=tutonum)
         {
             tutomove->Draw();
         }
         
         if (noammoflag == true)noammo->Draw();
     }
     if (playscene == 2)
     {
         if (tutocount == 0)tutogunpick1->Draw();
         if (tutocount== 1)tutogunpick2->Draw();
         if (tutocount == 2)tutopickup->Draw();
         if (noammoflag == true)noammo->Draw();
     }

     if (playscene == 3)
     {
         if (tutocount == 0)tutostage3->Draw();
         if (tutocount == 1)tutothrow->Draw();

         if (noammoflag == true)noammo->Draw();
     }

     if (playscene == 4)
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
    delete modelenemy;
    delete modelfloor;
    delete modelwall;
    delete modelBack;
    delete floor;
    delete backsphere;
    delete stagedata;

    delete player;


    

}

void GameScene::SwapEnemyData(XMFLOAT3& pos,XMFLOAT3& scale, int& modelname, float& r, bool& mod)
{
    enemypos.push_back(std::move(pos));
    enemyscale.push_back(std::move(scale));
    enemymodelname.push_back(std::move(modelname));
    enemyr.push_back(std::move(r));
    enemymod.push_back(std::move(mod));
    
}

void GameScene::SwapWallData(XMFLOAT3& pos, XMFLOAT3& scale, XMFLOAT3& rotation, int& modelname, XMFLOAT3& r,int& numcount)
{

    wallpos.push_back(std::move(pos));
    wallscale.push_back(std::move(scale));
    wallrotation.push_back(std::move(rotation));
    wallmodelname.push_back(std::move(modelname));
    wallr.push_back(std::move(r));
}
