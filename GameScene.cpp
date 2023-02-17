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


    //spriteCommon = new SpriteCommon();
    //spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    //debugText = new DebugText();
    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
    //const int debugTextTexNumber = 2;
    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
    //spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // �f�o�b�O�e�L�X�g������
    //debugText->Initialize(spriteCommon, debugTextTexNumber);

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
   /* spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");
    spriteCommon->LoadTexture(3, L"Resources/tuto.png");
    spriteCommon->LoadTexture(4, L"Resources/1432.png");*/


    collisionManager = CollisionManager::GetInstance();


    //FBX�֘A
    //�f�o�C�X���Z�b�g
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //�J�������Z�b�g
    FBXobj3d::SetCamera(camera);
    //FBX�p�C�v���C������
    FBXobj3d::CreateGraphicsPipeline();
    //file�ǂݍ���
    
    //model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");
    modelobjgun = FbxLoader::GetInstance()->LoadModelFromFile("gun");
    //modelglasswall = FbxLoader::GetInstance()->LoadModelFromFile("glasswall");


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

    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));


    ///1��
    for (int i = 0; i < 8; i++)
    {
        stage1wall[i] = nullptr;
        stage1wall[i] = new Wall();
        stage1wall[i]->Initialize();
        stage1wall[i]->SetModel(modelwall);
    }

    stage1wall[0]->SetPosition({ -10.0f,0.0f,0.0f });//���c
    stage1wall[0]->SetScale({ 0.01f,0.5f,0.1f });
    stage1wall[0]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    stage1wall[0]->WallInitialize();

    stage1wall[1]->SetPosition({ 30.0f,0.0f,0.0f });//�E�c
    stage1wall[1]->SetScale({ 0.01f,0.5f,0.5f });
    stage1wall[1]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,50.0f,0 }, 1.0f));
    stage1wall[1]->WallInitialize();

    stage1wall[2]->SetPosition({ 0.0f,0.0f,10.0f });//�O���тꉡ
    stage1wall[2]->SetRotation({ 0.0f,90.0f,0.0f });
    stage1wall[2]->SetScale({ 0.01f,0.5f,0.1f });
    stage1wall[2]->SetCollider(new BoxCollider(XMVECTOR{ 10.0f,100.0f,0.8f,0 }, 1.0f));
    stage1wall[2]->WallInitialize();

    stage1wall[3]->SetPosition({ 0.0f,0.0f,-10.0f });//��뉡
    stage1wall[3]->SetScale({ 0.01f,0.5f,1.0f });
    stage1wall[3]->SetRotation({ 0.0f,90.0f,0.0f });
    stage1wall[3]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage1wall[3]->WallInitialize();

    stage1wall[4]->SetPosition({ 10.0f,0.0f,42.5f });//�O�Ǐc��
    stage1wall[4]->SetScale({ 0.01f,1.0f,0.325f });
    stage1wall[4]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,32.5f,0 }, 1.0f));
    stage1wall[4]->WallInitialize();

    stage1wall[5]->SetPosition({ 20.0f,0.0f,75.0f });//����
    stage1wall[5]->SetScale({ 0.01f,1.0f,0.5f });
    stage1wall[5]->SetRotation({ 0.0f,90.0f,0.0f });
    stage1wall[5]->SetCollider(new BoxCollider(XMVECTOR{ 75.0f,100.0f,0.8f,0 }, 1.0f));
    stage1wall[5]->WallInitialize();

    stage1wall[6]->SetPosition({ 40.0f,0.0f,50.0f });//�����тꉡ
    stage1wall[6]->SetScale({ 0.01f,1.0f,0.1f });
    stage1wall[6]->SetRotation({ 0.0f,90.0f,0.0f });
    stage1wall[6]->SetCollider(new BoxCollider(XMVECTOR{ 10.0f,100.0f,0.8f,0 }, 1.0f));
    stage1wall[6]->WallInitialize();

    stage1wall[7]->SetPosition({ 50.0f,0.0f,70.0f });//���Ǐc
    stage1wall[7]->SetScale({ 0.01f,1.0f,0.5f });
    stage1wall[7]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,50.0f,0 }, 1.0f));
    stage1wall[7]->WallInitialize();

    //�ǂ̃X�P�[��0.1=���[���h��10

    //�G�֘A����
    ///�P��
    cube = new Enemy();
    cube->Initialize();
    cube->SetPosition({ 20.0f,5.0f,70.0f });
    cube->SetScale({ 0.01f,0.01f,0.01f });
    cube->SetModel(model2);
    cube->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
    cube->EnemyInitialize(TRUE);

    for (int i = 0; i < 5; i++)
    {
        Stage1[i] = nullptr;
        Stage1[i] = new Enemy();
        Stage1[i]->Initialize();
        Stage1[i]->SetScale({ 0.01f,0.01f,0.01f });
        Stage1[i]->SetModel(model2);
    }

    Stage1[0]->SetPosition({ 40.0f,5.0f,68.0f });
    Stage1[1]->SetPosition({ 150.0f,10.0f,10.0f });
    Stage1[2]->SetPosition({ 100.0f,5.0f,20.0f });
    Stage1[3]->SetPosition({ 350.0f,5.0f,5.0f });
    Stage1[4]->SetPosition({ 250.0f,10.0f,30.0f });

    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        Stage1[i]->EnemyInitialize(TRUE);
    }

     
    ///�Q��
    //��
    for (int i = 0; i < 6; i++)
    {
        stage2wall[i] = nullptr;
        stage2wall[i] = new Wall();
        stage2wall[i]->Initialize();
        stage2wall[i]->SetModel(modelwall);
    }
    
    //��
    stage2wall[0]->SetPosition({ -30.0f,10.0f,0.0f });
    stage2wall[0]->SetScale({ 0.1f,0.5f,1.0f });
    stage2wall[0]->SetRotation({ 0.0f,0.0f,0.0f });
    stage2wall[0]->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    stage2wall[0]->WallInitialize();

    //�O
    stage2wall[1]->SetPosition({ 0.0f,0.0f,80.0f });
    stage2wall[1]->SetScale({ 0.1f,1.0f,1.0f });
    stage2wall[1]->SetRotation({ 0.0f,90.0f,0.0f });
    stage2wall[1]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage2wall[1]->WallInitialize();

    //�E
    stage2wall[2]->SetPosition({ 70.0f,0.0f,0.0f });
    stage2wall[2]->SetScale({ 0.01f,1.0f,1.0f });
    stage2wall[2]->SetRotation({ 0.0f,0.0f,0.0f });
    stage2wall[2]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,100.0f,0 }, 1.0f));
    stage2wall[2]->WallInitialize();

    //���
    stage2wall[3]->SetPosition({ 0.0f,0.0f,-20.0f });
    stage2wall[3]->SetScale({ 0.1f,1.0f,1.0f });
    stage2wall[3]->SetRotation({ 0.0f,90.0f,0.0f });
    stage2wall[3]->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    stage2wall[3]->WallInitialize();

    //��O����
    stage2wall[4]->SetPosition({ -30.0f,0.0f,60.0f });
    stage2wall[4]->SetScale({ 0.1f,1.0f,0.5f });
    stage2wall[4]->SetRotation({ 0.0f,90.0f,0.0f });
    stage2wall[4]->SetCollider(new BoxCollider(XMVECTOR{ 50.0f,100.0f,0.8f,0 }, 1.0f));
    stage2wall[4]->WallInitialize();

    //�E�c��
    stage2wall[5]->SetPosition({ 10.0f,0.0f,0.0f });
    stage2wall[5]->SetScale({ 0.1f,1.0f,0.2f });
    stage2wall[5]->SetRotation({ 0.0f,0.0f,0.0f });
    stage2wall[5]->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,20.0f,0 }, 1.0f));
    stage2wall[5]->WallInitialize();


    //�e���
    gunstand= new Wall();
    gunstand->Initialize();
    gunstand->SetModel(model2);
    gunstand->SetPosition({ 0.0f,0.0f,10.0f });
    gunstand->SetScale({ 0.03f,0.04f,0.03f });
    gunstand->SetRotation({ 0.0f,0.0f,0.0f });
    gunstand->SetCollider(new BoxCollider(XMVECTOR{ 6.0f,6.0f,6.0f,0 }, 1.0f));
    gunstand->WallInitialize();

    //�e�{��
    tutogun = new Wall;
    tutogun->Initialize();
    tutogun->SetPosition({ 0.0f,6.0f,10.0f });
    tutogun->SetScale({ 0.01f,0.01f,0.01f });
    tutogun->SetModel(modelobjgun);
    tutogun->SetCollider(new BoxCollider(XMVECTOR{ 6.0f,6.0f,6.0f,0 }, 1.0f));
    tutogun->objgunInitialize();

    //�G2��
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

    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[

}

void GameScene::Update()
{

    if (input->PushKey(DIK_R))
    {
        resetflag = 1;
    }


    // �}�E�X�̓��͂��擾
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);

    //�`���[�g���A��
    if (scene==1)
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
        //�`��̂��߂ɃJ�����̍X�V���������Ăяo��


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
        cube->Update();
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
        for (int i = 0; i < 5; i++)
        {
         Stage1[i]->Update();
        }
    
    }


    //�Q�[���{��
    
    //�X�e�[�W�P
   if (scene==2)
    {
        //�`��̂��߂ɃJ�����̍X�V���������Ăяo��
        if (firstfrag == 1)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            /*player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->PlayerUpdate();*/
            firstfrag = 0;

        }

        
        //FBX�X�V
        floor->Update();
        cube->Update();
        cube->BulUpdate();
        player->BulUpdate();
        Stage1[0]->BulUpdate();
        backsphere->Update();
        player->BulUpdate();
        player->meleeUpdate();
        player->throwgunUpdate();
        player->gunUpdate(camera->GetTarget(), camera->GetmatRot());

        
        for (int i = 0; i < 5; i++)
        {
            Stage1[i]->Update();
        }


        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Update();
        }
       

        //�����������Ă�����X�V����
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            //�G�X�V
           cube->EnemyUpdate(player->GetPos());
            for (int i = 0; i < 1; i++)
            {
                Stage1[i]->EnemyUpdate(player->GetPos());
            }


            for (int i = 0; i < 8; i++)
            {
                stage1wall[i]->Update();
            }

            //�v���Cy�|�X�V
            player->Setoldpos(camera->GetEye());
            player->SetoldTarget(camera->GetTarget());
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            player->SetTarget(camera->GetTarget());
            player->SetPosition(camera->GetEye());
            player->SetRotation(camera->GetRoatation());
            player->PlayerUpdate(camera->GetTarget());
            player->gunUpdate(camera->GetTarget(),camera->GetmatRot());
           
        }
        
        
        if (mouseMove.lX != 0 || mouseMove.lY != 0)//�}�E�X���������Ă鎞
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
        

        //���ׂĂ̏Փ˂��`�F�b�N
        collisionManager->CheckAllCollisions();
        
        if (player->Getwallhit() == 1)
        {
            camera->SetTarget(player->GetTarget());
            camera->SetEye(player->GetPos());
        }
        
         

        //�v���C���[�ɓG������������V�[���J��
        if (player->Gethit()==1)
        {
            scene = 3;//�Q�[���I�[�o�[
        }

        //�G��|�����玟�̃X�e�[�W
        if (cube->GetScaleX()<check&&
            Stage1[0]->GetScaleX() < check)
           /* Stage1[1]->GetScaleX() < check&&
            Stage1[2]->GetScaleX() < check&&
            Stage1[3]->GetScaleX() < check&&
            Stage1[4]->GetScaleX() < check)*/
        {
            scene = 4;//�N���A
        }

    }

    //�X�e�[�W�Q
    if (scene==5)
    {

        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->SetPosition({ -1000.0f,10.0f,0.0f });
            stage1wall[i]->Update();
           
        }

        //�`��̂��߂ɃJ�����̍X�V���������Ăяo��
        if (firstfrag == 0)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            firstfrag = 1;

        }

        //FBX�X�V
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

        //�v���C���[�̏e�̃t���O�Ǘ�
        if (player->Gethave()==false)
        {
            player->Sethave(tutogun->Gethave());
        }
        if (player->Gethave() == true)
        {
            tutogun->Sethave(false);
        }
        


        //�����������Ă�����X�V����
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            //�G�X�V
            for (int i = 0; i < 3; i++)
            {
                Stage2[i]->EnemyUpdate(player->GetPos());
            }

            //�v���Cy�|�X�V
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


        if (mouseMove.lX != 0 || mouseMove.lY != 0)//�}�E�X���������Ă鎞
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


        //���ׂĂ̏Փ˂��`�F�b�N
        collisionManager->CheckAllCollisions();

        if (player->Getwallhit() == 1)
        {
            camera->SetTarget(player->GetTarget());
            camera->SetEye(player->GetPos());
            mouseMove.lX = 0;
            mouseMove.lY = 0;
        }



        //�v���C���[�ɓG������������V�[���J��
        if (player->Gethit() == 1)
        {
            scene = 3;//�Q�[���I�[�o�[
        }

        //�G��|�����玟�̃X�e�[�W
        //if (cube->GetScaleX() < check &&
        //    Stage1[0]->GetScaleX() < check)
        //    /* Stage1[1]->GetScaleX() < check&&
        //     Stage1[2]->GetScaleX() < check&&
        //     Stage1[3]->GetScaleX() < check&&
        //     Stage1[4]->GetScaleX() < check)*/
        //{
        //    scene = 4;//�N���A
        //}
    }

    //�Q�[���I�[�o�[
   if (scene==3)
   {
       //FBX�X�V
       floor->Update();
       for (int i = 0; i < 8; i++)
       {
           stage1wall[i]->Update();
       }
       cube->Update();
       player->BulUpdate();
       backsphere->Update();

       for (int i = 0; i < 5; i++)
       {
           Stage1[i]->Update();
       }

      
   }

   //�N���A
   if (scene == 4)
   {
       //�`��̂��߂ɃJ�����̍X�V���������Ăяo��
       if (firstfrag == 0)
       {
           camera->CurrentUpdate();
           camera->Update(WindowsApp::window_width, WindowsApp::window_height);

           firstfrag = 1;
       }

       //FBX�X�V
       floor->Update();
      /* wallLeft->Update();
       wallForward->Update();
       wallRight->Update();
       wallBack->Update();*/
       cube->Update();
       player->BulUpdate();
       //backsphere->Update();
      

       ////�����������Ă�����X�V����
       //if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
       //{

       //    //�v���Cy�|�X�V
       //    player->PlayerUpdate();

       //    camera->CurrentUpdate();
       //    camera->Update(WindowsApp::window_width, WindowsApp::window_height);
       //    playercol->SetPosition(player->GetPos());
       //    playercol->colUpdate();
       //}


       ////�}�E�X���������Ă鎞
       //if (mouseMove.lX != 0 || mouseMove.lY != 0)
       //{
       //    camera->CurrentUpdate();
       //    //camera->Update(WindowsApp::window_width, WindowsApp::window_height);

       //}

       ////���ׂĂ̏Փ˂��`�F�b�N
       //collisionManager->CheckAllCollisions();

   }
  


    //sprintf_s(pla, "WASD : move");

    //debugText->Print(pla, 0, 0, 1.0f);

}

void GameScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    //obj�`��O����
    Object3d::PreDraw(dxCommon->GetCommandList());
    //// �X�v���C�g�`��O����
    //spriteCommon->PreDraw();

    ////obj�A�X�v���C�g�̕`��
    ////tuto->Draw();
    //crosshair->Draw();
    //obj�̕`��㏈��
    Object3d::PostDraw();

    //FBX�`��
    if (scene==2)
    {
        for (int i = 0; i < 8; i++)
        {
            stage1wall[i]->Draw(cmdList);
        }
    }

    //�X�e�[�W�I�u�W�F�N�g
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
    
   
  
    //glasswallForward->Draw(cmdList);
    //glasswallLeft->Draw(cmdList);
    //gun->Draw(cmdList);
    //backsphere->Draw(cmdList);

    //�G�֘A
    
    if (scene==2)
    {
        cube->Draw(cmdList);//cube
        cube->BulDraw(cmdList);
        cube->PartDraw(cmdList);
        //Stage1[0]->BulDraw(cmdList);
        for (int i = 0; i < 1; i++)
        {
            Stage1[i]->Draw(cmdList);
            Stage1[i]->PartDraw(cmdList);
            Stage1[i]->BulDraw(cmdList);
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
     
    

    //�v���C���[�֘A
     player->throwgunDraw(cmdList);
     player->gunDraw(cmdList);
     player->BulDraw(cmdList);
    // player->meleeDraw(cmdList);
    

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();
}

void GameScene::restart()
{
  

    firstfrag = 1;

    //�v���C���[�֘A����
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
   


    //�G�֘A����
    
    cube->SetPosition({ 20.0f,5.0f,70.0f });
    cube->SetScale({ 0.01f,0.01f,0.01f });
    cube->setcol(0);
    
    cube->EnemyInitialize(TRUE);

    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->SetScale({ 0.01f,0.01f,0.01f });
        Stage1[i]->setcol(0);
        Stage1[i]->EnemyInitialize(TRUE);
    }

    Stage1[0]->SetPosition({ 40.0f,5.0f,68.0f });
    Stage1[1]->SetPosition({ 150.0f,10.0f,10.0f });
    Stage1[2]->SetPosition({ 100.0f,5.0f,20.0f });
    Stage1[3]->SetPosition({ 350.0f,5.0f,5.0f });
    Stage1[4]->SetPosition({ 250.0f,10.0f,30.0f });


   

    //FBX�X�V
   
    cube->Update();
    cube->BulUpdate();
    player->BulUpdate();
    backsphere->Update();

   
    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->Update();
        Stage1[0]->BulUpdate();
    }
    for (int i = 0; i < 8; i++)
    {
        stage1wall[i]->Update();
    }


}

void GameScene::transrationScene()
{
    if (scene==2)
    {
        //camera->SetEye(EyeInitialize);
        player->Sethave(true);
    }

    if (scene==5)
    {
        const XMFLOAT3 respos={0,0,0};
        player->Sethave(false);
        player->SetPosition(respos);
        camera->SetEye(respos);
    }
    
}
 

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

    delete cube;
    delete model2;
    delete modelfloor;
    delete modelwall;
    delete modelBack;
    delete floor;
    delete backsphere;

    delete player;

   

    for (int i = 0; i < 5; i++)
    {
        delete Stage1[i];
    }

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
