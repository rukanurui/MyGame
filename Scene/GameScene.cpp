#pragma once
#include "GameScene.h"
#include <cassert>
#include <iomanip>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include"SceneManager.h"

using namespace DirectX;

class ClearScene;
class GameoverScene;


template<>
BaseScene* BaseScene::makeScene<GameScene>() {
    return new GameScene();
}


void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon,WindowsApp*windows)
{
    //�|�C���^�u����
    
    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->Windows = windows;



    //�J��������
    camera = new Camera(this->input,this->Windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height,this->input);


#pragma region �`�揉��������


    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
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

    //�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
    spriteCommon->LoadTexture(101, L"Resources/White1x1.png");

    //�X�v���C�g����
    
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
    //�|�X�g�G�t�F�N�g�̏�����
    transEffect = TransEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);

    collisionManager = CollisionManager::GetInstance();


    //FBX�֘A
    //�f�o�C�X���Z�b�g
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //�J�������Z�b�g
    FBXobj3d::SetCamera(camera);
    //FBX�p�C�v���C������
    FBXobj3d::CreateGraphicsPipeline();
    //file�ǂݍ���
    
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");
    modelobjgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");


     //�w�i
    backsphere = new FBXobj3d;
    backsphere->Initialize();
    backsphere->SetPosition({ 0.0f,0.0f,0.0f });
    backsphere->SetScale({ 1.0f,1.0f,1.0f });
    backsphere->SetRotation({ 0.0f,0.0f,0.0f });
    backsphere->SetModel(modelBack);

    //�v���C���[�֘A����
    player = new Player();
    player->Initialize();
    player->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 0.5f));
    player->PlayerInitialize(this->input);
    player->SetPosition({ 0,4,0 });
    player->SetTarget({ 0,4,0 });


    //�n�`3d�I�u�W�F�N�g
    //��
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

    ////�ǂ̃X�P�[��0.1=���[���h��10
    

    //�e�{��
    tutogun = new Wall;
    tutogun->Initialize();
    tutogun->SetPosition({ 0.0f,6.0f,10.0f });
    tutogun->SetScale({ 0.01f,0.01f,0.01f });
    tutogun->SetModel(modelobjgun);
    tutogun->SetCollider(new BoxCollider(XMVECTOR{ 4.0f,4.0f,4.0f,0 }, 1.0f));
    tutogun->objgunInitialize();


    stagedata->InsertData(playscene,enemyNum,Enemys,wallNum,Walls,tutonum);


    //�G������
   /* uint32_t enemyNum = stagedata->GetEnemyNum();
    for (int i = 0; i < enemyNum; i++)
    {
        std::vector<Enemy> newenemy;
        newenemy[i].Initialize();



        enemys.push_back(newenemy[i]);

    }*/



    ////��
    //uint32_t wallNum = stageDatas[StageNum].wallNum;
    //for (int i = 0; i < wallNum; i++)
    //{
    //    std::vector<Wall> newwall;
    //    newwall[i].Initialize();



    //    walls.push_back(newwall[i]);

    //}

    ////�`���[�g���A��������
    //uint32_t tutoNum = stageDatas[StageNum].tutoNum;
    //for (int i = 0; i < tutoNum; i++)
    //{

    //}


    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[

}


void GameScene::Update()
{

    // �}�E�X�̓��͂��擾
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);


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


    //�Q�[���{��
    if (transscene == true)
    {
        //�`��̂��߂ɃJ�����̍X�V���������Ăяo��
        if (firstfrag == 1)
        {
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 0;

        }

        //�`���[�g���A��
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

        //�`���[�g���A��
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

        //�`���[�g���A��
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


        //FBX�X�V
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

        //�X�v���C�g�X�V
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


        //�����Ă��Ȃ���ԂōU��������
        if (tutonum >= tutocount)
        {
            if (input->PushclickLeft() && !input->PushKey(DIK_Q))
            {
                //�t���O��true�ɂ���
                attack = true;
            }

            if (attack == true)
            {
                movect++;

                //�G�X�V
                for (std::unique_ptr<Enemy>& enemy : Enemys)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }

                for (std::unique_ptr<Wall>& wall : Walls)
                {
                    wall->Update();
                }

                //�v���Cy�|�X�V
                player->Setoldpos(camera->GetEye());
                player->SetoldTarget(camera->GetTarget());
                camera->CurrentUpdate(player->GetVelocity());
                camera->Update(WindowsApp::window_width, WindowsApp::window_height);
                player->SetTarget(camera->GetTarget());
                player->SetPosition(camera->GetEye());
                player->SetRotation(camera->GetRoatation());
                player->PlayerUpdate(camera->GetTarget());
                player->gunUpdate(camera->GetTarget(), camera->GetEye());

                //�c�e���̎擾
                magazin = player->Getmagazin();
                //�e�������Ă��邩
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

            //�G�X�V
            for (std::unique_ptr<Enemy>& enemy : Enemys)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            //�v���Cy�|�X�V
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate(player->GetVelocity());
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(), camera->GetEye());

            //�c�e���̎擾
            magazin = player->Getmagazin();
            //�e�������Ă��邩
            have = player->Gethave();

            if (movect >= 15)
            {
                attack = false;
                movect = 0;
            }
        }

        //�����Ă��Ȃ���Ԃŏe�𓊂�����
        if (input->PushclickRight() && !input->PushclickLeft())
        {
            gunthrow = true;
        }

        if (gunthrow == true)
        {
            movect++;

            //�G�X�V
            for (std::unique_ptr<Enemy>& enemy : Enemys)
            {
                enemy->EnemyUpdate(player->GetPos());
            }

            for (std::unique_ptr<Wall>& wall : Walls)
            {
                wall->Update();
            }

            //�v���Cy�|�X�V
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

            //�c�e���̎擾
            magazin = player->Getmagazin();
            //�e�������Ă��邩
            have = player->Gethave();

            if (movect >= 15)
            {
                gunthrow = false;
                movect = 0;
            }
        }

        timecount++;

        //�e���Ȃ��Ƃ�
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

        //�ǂɓ�����O�̍��W
        camera->SetWallEye(camera->GetEye());
        camera->SetWallTarget(camera->GetTarget());


        //�����������Ă�����X�V����
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            if (tutonum >= tutocount)
            {
                //�G�X�V
                for (std::unique_ptr<Enemy>& enemy : Enemys)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }
            }


            //�v���Cy�|�X�V
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
                //�G�X�V
                for (std::unique_ptr<Enemy>& enemy : Enemys)
                {
                    enemy->EnemyUpdate(player->GetPos());
                }
            }

            //�v���Cy�|�X�V
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

        //�}�E�X���������Ă鎞
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

        //���ׂĂ̏Փ˂��`�F�b�N
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

        //�v���C���[�ɓG������������V�[���J��
        if (player->Gethit() == 1)
        {
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<GameoverScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            //���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
            sceneManager->SetplayScene(playscene);
        }

        //�p�[�e�B�N���o���I������烊�X�g�폜
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

        //�G�S���|������N���A
        if (Enemys.size() == 0)
        {
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<ClearScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            //���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
            sceneManager->SetplayScene(playscene);

        }
    }

}




void GameScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

   

    for (std::unique_ptr<Wall>& wall : Walls)
    {
        wall->Draw(cmdList);
    }

    //�X�e�[�W�I�u�W�F�N�g
    floor->Draw(cmdList);

    //�G�֘A
    for (std::unique_ptr<Enemy>& enemy : Enemys)
    {
        enemy->BulDraw(cmdList);
        enemy->PartDraw(cmdList);
        enemy->Draw(cmdList);
    }
    

    //�v���C���[�֘A
    player->Draw(cmdList);

     //�X�v���C�g�`��O����
     spriteCommon->PreDraw();

     //�V�[���؂�ւ�����
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
    

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();
}


//void GameScene::transrationScene()
//{
//    //�X�e�[�W1
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
//    //�X�e�[�W2
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
//        ////list�̍폜
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
//    //�X�e�[�W3
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
//    //�X�e�[�W4
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
//        ////list�̍폜
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
    //3d�I�u�W�F�N�g���
    //delete object3d;
    //3d���f�����
    //delete Model;

    //�f�o�b�O�e�L�X�g���
    //debugText->Finalize();
    delete debugText;

    //�X�v���C�g���
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
