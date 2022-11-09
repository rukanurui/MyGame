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

    debugText = new DebugText();
    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
    const int debugTextTexNumber = 2;
    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // �f�o�b�O�e�L�X�g������
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");
    spriteCommon->LoadTexture(3, L"Resources/tuto.png");
    spriteCommon->LoadTexture(4, L"Resources/1432.png");

    
    //�X�v���C�g�̐���
    //Sprite* tuto = Sprite::Create(spriteCommon, 3);
    //tuto->SetPosition({ 0,0,0 });
    //tuto->SetRotation({ (float)(rand() % 360) });
    //tuto->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //tuto->TransferVertexBuffer();

    //Sprite* tex = Sprite::Create(spriteCommon, 1);
    //tex->SetPosition({ 100,100,0 });
    //tex->SetRotation({ (float)(rand() % 360) });
    //tuto->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //tex->TransferVertexBuffer();

    //Sprite* crosshair = Sprite::Create(spriteCommon, 4);
    //crosshair->Create(spriteCommon, 4);
    //crosshair->SetPosition({Windows->window_width/2,Windows->window_height/2,0 });
    ///*crosshair->SetRotation({ (float)(rand() % 360) });*/
    //tuto->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
    //crosshair->TransferVertexBuffer();




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

    //�n�`3d�I�u�W�F�N�g
    //��
    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

         
    //��
    wall = new Wall;
    wall->Initialize();
    wall->SetPosition({ -30.0f,10.0f,0.0f });
    wall->SetScale({ 0.1f,0.5f,1.0f });
    wall->SetRotation({ 0.0f,0.0f,0.0f });
    wall->SetModel(modelwall);
    wall->SetCollider(new BoxCollider(XMVECTOR{ 0.5f,100.0f,100.0f,0 }, 1.0f));
    wall->WallInitialize();

    wall2 = new Wall;
    wall2->Initialize();
    wall2->SetPosition({ 0.0f,0.0f,100.0f });
    wall2->SetScale({ 0.1f,1.0f,1.0f });
    wall2->SetRotation({ 0.0f,90.0f,0.0f });
    wall2->SetModel(modelwall);
    wall2->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,100.0f,0.8f,0 }, 1.0f));
    wall2->WallInitialize();

    wall3 = new Wall;
    wall3->Initialize();
    wall3->SetPosition({ 100.0f,0.0f,0.0f });
    wall3->SetScale({ 0.01f,0.1f,0.1f });
    wall3->SetRotation({ 0.0f,0.0f,0.0f });
    wall3->SetModel(modelwall);
    wall3->SetCollider(new BoxCollider(XMVECTOR{ 0.8f,100.0f,100.0f,0 }, 1.0f));
    wall3->WallInitialize();

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
    
    
    //FBX�X�V

    
    floor->Update();
    wall->Update();
    wall2->Update();
    wall3->Update();
    cube->Update();

    for (int i = 0; i < 5; i++)
    {
        Stage1[i]->Update();
    }

    for (int i = 0; i < 20; i++)
    {
        PartCube1[i]->Update();
        PartCube2[i]->Update();
        PartCube3[i]->Update();
        PartCube4[i]->Update();
        PartCube5[i]->Update();
        PartCube6[i]->Update();
    }

    camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);

    

    //�Q�[���{��
    
    player->PlayerUpdate();

    //ballet->Update();
    
    cube->EnemyUpdate();

    XMFLOAT3 bulpos = ballet->GetPos();
    XMFLOAT3 epos = cube->GetPos();

    for (int i = 0; i < 20; i++)
    {
        PartCube1[i]->PartUpdate(cube->GetPos());
        PartCube2[i]->PartUpdate(Stage1[0]->GetPos());
        PartCube3[i]->PartUpdate(Stage1[1]->GetPos());
        PartCube4[i]->PartUpdate(Stage1[2]->GetPos());
        PartCube5[i]->PartUpdate(Stage1[3]->GetPos());
        PartCube6[i]->PartUpdate(Stage1[4]->GetPos());
    }



    //���ׂĂ̏Փ˂��`�F�b�N
    collisionManager->CheckAllCollisions();

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
    wall->Draw(cmdList);
    wall2->Draw(cmdList);
    wall3->Draw(cmdList);

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
    debugText->DrawAll();
}

    

void GameScene::Finalize()
{
    //3d�I�u�W�F�N�g���
    //delete object3d;
    //3d���f�����
    //delete Model;

    //�f�o�b�O�e�L�X�g���
    debugText->Finalize();
    delete debugText;

    //�X�v���C�g���
    //for (auto& sprite : sprites) {
    //    delete sprite;
    //}
    //sprites.clear();

    delete model1;
    delete cube;
    delete model2;
}
