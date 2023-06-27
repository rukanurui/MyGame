#pragma once
#include "GameScene.h"
#include <cassert>
#include <iomanip>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include"SceneManager.h"
#include"StageData.h"

using namespace DirectX;
XMFLOAT3 GameScene::enemypos = { 0,0,0 };
XMFLOAT3 GameScene::enemyscale = { 0,0,0 };
int GameScene::enemymodelname=0;//モデルの指定
float GameScene::enemyr=0;//コライダーの半径指定
bool GameScene::emod=0;//敵の種類の指定


XMFLOAT3 GameScene::wallpos{ 0,0,0 };//座標
XMFLOAT3 GameScene::wallscale{ 0,0,0 };//スケール
XMFLOAT3 GameScene::wallrotation{ 0,0,0 };
int GameScene::wallmodelname=0;//モデルの指定
XMFLOAT3 GameScene::wallr{ 0,0,0 };//コライダーの半径指定

int GameScene::tutonum = 0;
int GameScene::enemyNum = 0;
int  GameScene::wallNum = 0;

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
    stagedata = new StageData;

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
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelobjgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");


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
    

    //銃本体
    tutogun = new Wall;
    tutogun->Initialize();
    tutogun->SetPosition({ 0.0f,6.0f,10.0f });
    tutogun->SetScale({ 0.01f,0.01f,0.01f });
    tutogun->SetModel(modelobjgun);
    tutogun->SetCollider(new BoxCollider(XMVECTOR{ 4.0f,4.0f,4.0f,0 }, 1.0f));
    tutogun->objgunInitialize();


    //ステージデータ読み取り
    stagedata->InsertData(playscene,tutonum,enemyNum,wallNum);

    //敵の生成
    for (int i = 0; i < enemyNum; i++)
    {
        std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
        newenemy->Initialize();
        newenemy->SetPosition({ enemypos.x,enemypos.y,enemypos.z });
        newenemy->SetScale({ enemyscale.x,enemyscale.y,enemyscale.z });
        if (enemymodelname == 1)
        {
            newenemy->SetModel(model2);
        }
        newenemy->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, enemyr));
        if (emod == 0)
        {
            newenemy->EnemyInitialize(TRUE);
        }
        else if (emod == 1)
        {
            newenemy->EnemyInitialize(FALSE);
        }
        Enemys.push_back(std::move(newenemy));
    }
    
    for (int i = 0; i < wallNum; i++)
    {
        std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
          newwall->Initialize();
          newwall->SetPosition({ wallpos.x,wallpos.y,wallpos.z });
          newwall->SetScale({ wallscale.x,wallscale.y,wallscale.z });
          newwall->SetRotation({ wallrotation.x,wallrotation.y,wallrotation.z });
          if (wallmodelname == 1)
         {
             newwall->SetModel(modelwall);
          }
         else if (wallmodelname == 2)
         {
             newwall->SetModel(model2);
          }
          newwall->SetCollider(new BoxCollider(XMVECTOR{ wallr.x,wallr.y,wallr.z,0 }, 1.0f));
          Walls.push_back(std::move(newwall));
    }
   


    int counter = 0; // アニメーションの経過時間カウンター

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
            //transrationScene();
            transcount = 0.0f;
            transscene = true;
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
                        tutocount++;
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
                        spritesize.x -= 1.0f;
                        spritesize.y -= 1.0f;
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
                        tutocount++;
                        wait = 0;
                    }
                }
            }
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
                        spritesize.x -= 1.0f;
                        spritesize.y -= 1.0f;
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
                        spritesize.x -= 1.0f;
                        spritesize.y -= 1.0f;
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

                if (tutoscene == 3)
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
                        tutocount++;
                        wait = 0;

                    }
                }
            }
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
                        spritesize.x -= 2.0f;
                        spritesize.y -= 2.0f;
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

                if (tutoscene == 1)
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
                        tutocount++;
                        wait = 0;

                    }
                }
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

        for (std::unique_ptr<Enemy>& enemy : Enemys)
        {
            enemy->PartUpdate();
            enemy->BulUpdate();
            enemy->Update();
        }

        for (std::unique_ptr<Wall>& wall : Walls)
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
        if (tutonum >= tutocount)
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
                for (std::unique_ptr<Enemy>& enemy : Enemys)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }

                for (std::unique_ptr<Wall>& wall : Walls)
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
            for (std::unique_ptr<Enemy>& enemy : Enemys)
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
            for (std::unique_ptr<Enemy>& enemy : Enemys)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Walls)
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

            if (tutonum >= tutocount)
            {
                //敵更新
                for (std::unique_ptr<Enemy>& enemy : Enemys)
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

    //敵関連
    for (std::unique_ptr<Enemy>& enemy : Enemys)
    {
        enemy->BulDraw(cmdList);
        enemy->PartDraw(cmdList);
        enemy->Draw(cmdList);
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

     if (playscene == 1)
     {
         if (tutoscene == 0)tutomove->Draw();
         if (tutoscene == 1)tutomouse->Draw();
         if (tutoscene == 2)tutorule->Draw();
         if (noammoflag == true)noammo->Draw();
     }
     if (playscene == 2)
     {
         if (tutoscene == 3)tutogunpick1->Draw();
         if (tutoscene == 4)tutogunpick2->Draw();
         if (tutoscene == 5)tutopickup->Draw();
         if (noammoflag == true)noammo->Draw();
     }

     if (playscene == 3)
     {
         if (tutoscene == 6)tutostage3->Draw();
         if (tutoscene == 7)tutothrow->Draw();

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


//void GameScene::transrationScene()
//{
//    //ステージ1
//    if (playscene==1)
//    {
//
//        const XMFLOAT3 respos = { 0,5,0 };
//
//        camera->SetTarget({ 0, 5, 0 });
//        camera->SetEye(respos);
//        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
//        camera->CurrentUpdate(player->GetVelocity());
//
//        player->Sethave(true);
//        player->SetPosition(camera->GetEye());
//        player->PlayerUpdate(camera->GetTarget());
//
//        tutoscene = 0;
//
//        LoadEnemyDataS1();
//        SwapEnemyDataS1();
//        LoadWallDataS1();
//        SwapWallDataS1();
//
//    }
//
//    //ステージ2
//    if (playscene==2)
//    {
//        const XMFLOAT3 respos={0,5,0};
//       
//        camera->SetTarget({ 0, 5, 0 });
//        camera->SetEye(respos);
//        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
//        camera->CurrentUpdate(player->GetVelocity());
//
//        player->Sethave(false);
//        player->SetPosition(camera->GetEye());
//        player->PlayerUpdate(camera->GetTarget());
//
//        tutoscene = 3;
//       
//        LoadEnemyDataS2();
//        SwapEnemyDataS2();
//        LoadWallDataS2();
//        SwapWallDataS2();
//
//        magazin = 5;
//        player->SetMagazin(magazin);
//
//        ////listの削除
//        //Stage1Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
//        //    return enemy->die;
//        //    });
//        //Stage1Walls.remove_if([](std::unique_ptr<Wall>& wall) {
//        //    return wall->die;
//        //    });
//
//        for (std::unique_ptr<Enemy>& enemy : Stage2Enemy)
//        {
//            enemy->PartUpdate();
//            enemy->BulUpdate();
//            enemy->Update();
//        }
//        for (std::unique_ptr<Wall>& wall : Stage2Walls)
//        {
//            wall->Update();
//        }
//
//    }
//
//    //ステージ3
//    if (playscene==3)
//    {
//        const XMFLOAT3 respos = { 0,5,0 };
//        camera->SetTarget({ 0, 5, 0 });
//        camera->SetEye(respos);
//        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
//        camera->CurrentUpdate(player->GetVelocity());
//
//        magazin = 0;
//        player->SetMagazin(magazin);
//        player->Sethave(true);
//        player->SetPosition(camera->GetEye());
//        player->PlayerUpdate(camera->GetTarget());
//
//        tutoscene = 6;
//
//        LoadEnemyDataS3();
//        SwapEnemyDataS3();
//       LoadWallDataS3();
//        SwapWallDataS3();
//     
//        tutogun->SetPosition({ 0.0f,0.0f,20.0f });
//        tutogun->Update();
//
//    }
//
//    //ステージ4
//    if (playscene == 4)
//    {
//        const XMFLOAT3 respos = { 0,5,0 };
//        player->Sethave(false);
//        camera->SetTarget({ 0, 5, 0 });
//        camera->SetEye(respos);
//        camera->Update(WindowsApp::window_width, WindowsApp::window_height);
//        camera->CurrentUpdate(player->GetVelocity());
//
//        magazin = 5;
//        player->SetMagazin(magazin);
//        player->SetPosition(camera->GetEye());
//        player->PlayerUpdate(camera->GetTarget());
//        player->Sethave(true);
//
//        LoadEnemyDataS4();
//        SwapEnemyDataS4();
//        LoadWallDataS4();
//        SwapWallDataS4();
//
//
//        ////listの削除
//        //Stage3Enemy.remove_if([](std::unique_ptr<Enemy>& enemy) {
//        //    return enemy->die;
//        //    });
//        //Stage3Walls.remove_if([](std::unique_ptr<Wall>& wall) {
//        //    return wall->die;
//        //    });
//
//        tutogun->SetPosition({ 0.0f,0.0f,30.0f });
//        tutogun->Update();
//
//    }
//    
//}
// 

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
    delete stagedata;

    delete player;


    

}

void GameScene::SwapEnemyData(XMFLOAT3 pos,XMFLOAT3 scale, int modelname, float r, bool mod, int stage, int nextflag)
{
    
    enemypos = pos;
    enemyscale = scale;
    enemymodelname = modelname;
    enemyr = r;
    emod = mod;

   /* newenemy->SetPosition({ pos.x,pos.y,pos.z });
    newenemy->SetScale({ scale.x,scale.y,scale.z });
    if (modelname == 1)
    {
        newenemy->SetModel(model2);
    }
    newenemy->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, r));
    if (mod == 0)
    {
        newenemy->EnemyInitialize(TRUE);
    }
    else if (mod == 1)
    {
        newenemy->EnemyInitialize(FALSE);
    }
    Enemys.push_back(std::move(newenemy));*/
    

}

void GameScene::SwapWallData(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rotation, int modelname, XMFLOAT3 r, int nextflag)
{
    wallpos = pos;
    wallscale = scale;
    wallrotation = rotation;
    wallmodelname = modelname;
    wallr = r;
   
   /* newwall->Initialize();
    newwall->SetPosition({ pos.x,pos.y,pos.z });
    newwall->SetScale({ scale.x,scale.y,scale.z });
    newwall->SetRotation({ rotation.x,rotation.y,rotation.z });
    if (modelname == 1)
    {
        newwall->SetModel(modelwall);
    }
    else if (modelname == 2)
    {
        newwall->SetModel(model2);
    }
    newwall->SetCollider(new BoxCollider(XMVECTOR{ r.x,r.y,r.z,0 }, 1.0f));
    Walls.push_back(std::move(newwall));*/
}
