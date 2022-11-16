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
    const int debugTextTexNumber = 2;
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
    
    model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");
    modelBack = FbxLoader::GetInstance()->LoadModelFromFile("back");

    //�n�`3d�I�u�W�F�N�g
    //��
    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

         
    //��
    wallLeft = new Wall;
    wallLeft->Initialize();
    wallLeft->SetPosition({ -30.0f,10.0f,0.0f });
    wallLeft->SetScale({ 0.1f,0.5f,1.0f });
    wallLeft->SetRotation({ 0.0f,0.0f,0.0f });
    wallLeft->SetModel(modelwall);
    wallLeft->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    wallLeft->WallInitialize();

    wallForward = new Wall;
    wallForward->Initialize();
    wallForward->SetPosition({ 0.0f,0.0f,100.0f });
    wallForward->SetScale({ 0.1f,1.0f,1.0f });
    wallForward->SetRotation({ 0.0f,90.0f,0.0f });
    wallForward->SetModel(modelwall);
    wallForward->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    wallForward->WallInitialize();

    wallRight = new Wall;
    wallRight->Initialize();
    wallRight->SetPosition({ 100.0f,0.0f,0.0f });
    wallRight->SetScale({ 0.01f,1.0f,1.0f });
    wallRight->SetRotation({ 0.0f,0.0f,0.0f });
    wallRight->SetModel(modelwall);
    wallRight->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,100.0f,0 }, 1.0f));
    wallRight->WallInitialize();

    wallBack = new Wall;
    wallBack->Initialize();
    wallBack->SetPosition({ 0.0f,0.0f,-25.0f });
    wallBack->SetScale({ 0.1f,1.0f,1.0f });
    wallBack->SetRotation({ 0.0f,90.0f,0.0f });
    wallBack->SetModel(modelwall);
    wallBack->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    wallBack->WallInitialize();

    //�w�i
    backsphere = new FBXobj3d;
    backsphere->Initialize();
    backsphere->SetPosition({ 0.0f,0.0f,0.0f });
    backsphere->SetScale({ 1.0f,1.0f,1.0f });
    backsphere->SetRotation({ 0.0f,0.0f,0.0f });
    backsphere->SetModel(modelBack);

    //�v���C���[�֘A����
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

    playercol = new PlayerCol;
    playercol->Initialize();
    playercol->SetPosition({ 0,0,0 });
    playercol->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 0.5f));
    

    //�G�֘A����
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
    player->SetmouseX(CurretmouseX);
    player->SetmouseY(CurretmouseY);

    //�X�v���C�g�X�V
    //tex->Update();
    //tuto->Update();
    //crosshair->Update();

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
        wallLeft->Update();
        wallForward->Update();
        wallRight->Update();
        wallBack->Update();
        cube->Update();
        ballet->Update();
        backsphere->Update();
        for (int i = 0; i < 20; i++)
        {
         PartCube1[i]->Update();
         PartCube2[i]->Update();
         PartCube3[i]->Update();
         PartCube4[i]->Update();
         PartCube5[i]->Update();
         PartCube6[i]->Update();
        }
        for (int i = 0; i < 5; i++)
        {
         Stage1[i]->Update();
        }
    
    }


    //�Q�[���{��
   if (scene==2)
    {
        //�`��̂��߂ɃJ�����̍X�V���������Ăяo��
        if (firstfrag == 1)
        {
            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);

            firstfrag = 0;
        }

        //FBX�X�V
        floor->Update();
        wallLeft->Update();
        wallForward->Update();
        wallRight->Update();
        wallBack->Update();
        cube->Update();
        ballet->Update();
        backsphere->Update();
        for (int i = 0; i < 20; i++)
        {
            PartCube1[i]->Update();
            PartCube2[i]->Update();
            PartCube3[i]->Update();
            PartCube4[i]->Update();
            PartCube5[i]->Update();
            PartCube6[i]->Update();
        }
        for (int i = 0; i < 5; i++)
        {
            Stage1[i]->Update();
        }

        //�����������Ă�����X�V����
        if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
        {

            //�G�X�V
            cube->EnemyUpdate(player->GetEye());
            for (int i = 0; i < 5; i++)
            {
                Stage1[i]->EnemyUpdate(player->GetEye());
            }

            //particle�X�V        
            for (int i = 0; i < 20; i++)
            {
                PartCube1[i]->PartUpdate(cube->GetPos());
                PartCube2[i]->PartUpdate(Stage1[0]->GetPos());
                PartCube3[i]->PartUpdate(Stage1[1]->GetPos());
                PartCube4[i]->PartUpdate(Stage1[2]->GetPos());
                PartCube5[i]->PartUpdate(Stage1[3]->GetPos());
                PartCube6[i]->PartUpdate(Stage1[4]->GetPos());
            }

            //�v���Cy�|�X�V
            player->PlayerUpdate();

            camera->CurrentUpdate();
            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
            playercol->SetPosition(player->GetEye());
            playercol->colUpdate();
        }


        //�}�E�X���������Ă鎞
        if (mouseMove.lX != 0 || mouseMove.lY != 0)
        {
            camera->CurrentUpdate();
            //camera->Update(WindowsApp::window_width, WindowsApp::window_height);

        }

        //���ׂĂ̏Փ˂��`�F�b�N
        collisionManager->CheckAllCollisions();

        //�v���C���[�ɓG������������V�[���J��
        if (playercol->Gethit()==1)
        {
            scene = 3;//�Q�[���I�[�o�[
        }

        if (cube->GetScaleX()<check&&
            Stage1[0]->GetScaleX() < check&&
            Stage1[1]->GetScaleX() < check&&
            Stage1[2]->GetScaleX() < check&&
            Stage1[3]->GetScaleX() < check&&
            Stage1[4]->GetScaleX() < check)
        {
            scene = 4;//�N���A
        }

    }

   if (scene==3)
   {
       //FBX�X�V
       floor->Update();
       wallLeft->Update();
       wallForward->Update();
       wallRight->Update();
       wallBack->Update();
       cube->Update();
       ballet->Update();
       backsphere->Update();
       for (int i = 0; i < 20; i++)
       {
           PartCube1[i]->Update();
           PartCube2[i]->Update();
           PartCube3[i]->Update();
           PartCube4[i]->Update();
           PartCube5[i]->Update();
           PartCube6[i]->Update();
       }
       for (int i = 0; i < 5; i++)
       {
           Stage1[i]->Update();
       }
       //particle�X�V        
       for (int i = 0; i < 20; i++)
       {
           PartCube1[i]->PartUpdate(cube->GetPos());
           PartCube2[i]->PartUpdate(Stage1[0]->GetPos());
           PartCube3[i]->PartUpdate(Stage1[1]->GetPos());
           PartCube4[i]->PartUpdate(Stage1[2]->GetPos());
           PartCube5[i]->PartUpdate(Stage1[3]->GetPos());
           PartCube6[i]->PartUpdate(Stage1[4]->GetPos());
       }
   }

   if (scene == 4)
   {
       //FBX�X�V
       floor->Update();
       wallLeft->Update();
       wallForward->Update();
       wallRight->Update();
       wallBack->Update();
       cube->Update();
       ballet->Update();
       backsphere->Update();
       for (int i = 0; i < 20; i++)
       {
           PartCube1[i]->Update();
           PartCube2[i]->Update();
           PartCube3[i]->Update();
           PartCube4[i]->Update();
           PartCube5[i]->Update();
           PartCube6[i]->Update();
       }
       for (int i = 0; i < 5; i++)
       {
           Stage1[i]->Update();
       }
       //particle�X�V        
       for (int i = 0; i < 20; i++)
       {
           PartCube1[i]->PartUpdate(cube->GetPos());
           PartCube2[i]->PartUpdate(Stage1[0]->GetPos());
           PartCube3[i]->PartUpdate(Stage1[1]->GetPos());
           PartCube4[i]->PartUpdate(Stage1[2]->GetPos());
           PartCube5[i]->PartUpdate(Stage1[3]->GetPos());
           PartCube6[i]->PartUpdate(Stage1[4]->GetPos());
       }
   }
  

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

    //�X�e�[�W�I�u�W�F�N�g
    floor->Draw(cmdList);
    wallLeft->Draw(cmdList);
    wallForward->Draw(cmdList);
    wallRight->Draw(cmdList);
    wallBack->Draw(cmdList);
    //backsphere->Draw(cmdList);

    //�G�֘A
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

    ////�v���C���[�֘A
    ballet->Draw(cmdList);

    

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();
}

void GameScene::restart()
{
    //�n�`3d�I�u�W�F�N�g
    //��    
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));


    //��
    wallLeft->SetPosition({ -30.0f,10.0f,0.0f });
    wallLeft->SetScale({ 0.1f,0.5f,1.0f });
    wallLeft->SetRotation({ 0.0f,0.0f,0.0f });
    wallLeft->SetModel(modelwall);
    wallLeft->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    wallLeft->WallInitialize();

    wallForward->SetPosition({ 0.0f,0.0f,100.0f });
    wallForward->SetScale({ 0.1f,1.0f,1.0f });
    wallForward->SetRotation({ 0.0f,90.0f,0.0f });
    wallForward->SetModel(modelwall);
    wallForward->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    wallForward->WallInitialize();

    wallRight->SetPosition({ 100.0f,0.0f,0.0f });
    wallRight->SetScale({ 0.01f,1.0f,1.0f });
    wallRight->SetRotation({ 0.0f,0.0f,0.0f });
    wallRight->SetModel(modelwall);
    wallRight->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,100.0f,0 }, 1.0f));
    wallRight->WallInitialize();

    wallBack->SetPosition({ 0.0f,0.0f,-20.0f });
    wallBack->SetScale({ 0.1f,1.0f,1.0f });
    wallBack->SetRotation({ 0.0f,90.0f,0.0f });
    wallBack->SetModel(modelwall);
    wallBack->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    wallBack->WallInitialize();

    //�w�i
    
    backsphere->SetPosition({ 0.0f,0.0f,0.0f });
    backsphere->SetScale({ 1.0f,1.0f,1.0f });
    backsphere->SetRotation({ 0.0f,0.0f,0.0f });
    backsphere->SetModel(modelBack);

    //�v���C���[�֘A����
    ballet->SetPosition({ 500.0f,5.0f,0.0f });
    ballet->SetScale({ 0.01f,0.01f,0.01f });
    ballet->SetModel(modelballet);
    ballet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
    ballet->BulInitialize();

    player = new Player(ballet);
    player->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);
    player->PlayerInitialize(this->input);

    
    playercol->SetPosition({ 0,0,0 });
    playercol->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 0.5f));


    //�G�֘A����
    
    cube->SetPosition({ 5.0f,5.0f,20.0f });
    cube->SetScale({ 0.01f,0.01f,0.01f });
    cube->SetModel(model2);
    cube->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
    cube->EnemyInitialize();

    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->SetScale({ 0.01f,0.01f,0.01f });
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
        PartCube1[i]->SetPosition({ 5.0f,5.0f,20.0f });
        PartCube1[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube1[i]->SetModel(model2);
        PartCube1[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube1[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
      
        PartCube2[i]->SetPosition({ 15.0f,5.0f,10.0f });
        PartCube2[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube2[i]->SetModel(model2);
        PartCube2[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube2[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
       
        PartCube3[i]->SetPosition({ 15.0f,10.0f,10.0f });
        PartCube3[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube3[i]->SetModel(model2);
        PartCube3[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube3[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
       
        PartCube4[i]->SetPosition({ 10.0f,5.0f,20.0f });
        PartCube4[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube4[i]->SetModel(model2);
        PartCube4[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube4[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
       
        PartCube5[i]->SetPosition({ 35.0f,5.0f,5.0f });
        PartCube5[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube5[i]->SetModel(model2);
        PartCube5[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube5[i]->PartInitialize();
    }

    for (int i = 0; i < 20; i++)
    {
       
        PartCube6[i]->SetPosition({ 25.0f,10.0f,30.0f });
        PartCube6[i]->SetScale({ 0.005f,0.005f,0.005f });
        PartCube6[i]->SetModel(model2);
        PartCube6[i]->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 1.0f));
        PartCube6[i]->PartInitialize();
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

    

    delete model1;
    delete cube;
    delete model2;
    delete modelballet;
    delete modelfloor;
    delete modelwall;
    delete modelBack;

    delete ballet;
    delete wallBack;
    delete wallForward;
    delete wallLeft;
    delete wallRight;
    delete floor;
    delete backsphere;

    for (int i = 0; i < 20; i++)
    {
        delete PartCube1[i];
        delete PartCube2[i];
        delete PartCube3[i];
        delete PartCube4[i];
        delete PartCube5[i];
        delete PartCube6[i];
    }

    for (int i = 0; i < 5; i++)
    {
        delete Stage1[i];
    }

}
