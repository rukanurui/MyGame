#pragma once
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include"CollisionManager.h"


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
    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("wall");
    modelballet = FbxLoader::GetInstance()->LoadModelFromFile("bullet");

    Otin = new FBXobj3d;
    Otin->Initialize();
    Otin->SetPosition({ 0.0f,0.0f,0.0f });
    Otin->SetModel(model1);

    cube = new Enemy;
    cube->Initialize();
    cube->SetPosition({ 5.0f,5.0f,20.0f });
    cube->SetScale({ 1.0f,1.0f,1.0f });
    cube->SetModel(model2);
    cube->SetCollider(new SphereCollider(XMVECTOR{ 0,5.0f,0,0 },5.0f));

    //���U����G
    for (int i = 0; i < 8; i++)
    {
        DivCube[i] = nullptr;
        DivCube[i] = new Enemy;
        DivCube[i]->Initialize();
        if (i<=1)
        {
            DivCube[i]->SetPosition({ 100.0f + 1.0f * i,5.0f,20.0f});
        }
        if (i >1&&i<=3)
        {
            DivCube[i]->SetPosition({ 100.0f + 1.0f * i-2.0f,5.0f-1.0f,20.0f });
        }
        if (i > 3 && i <= 5)
        {
            DivCube[i]->SetPosition({ 100.0f + 1.0f * i-4,5.0f,21.0f });
        }
        if (i > 5 && i <= 8)
        {
            DivCube[i]->SetPosition({ 100.0f + 1.0f * i-6 ,5.0f-1.0f,21.0f });
        }
        DivCube[i]->SetScale({ 0.5f,0.5f,0.5f });
        DivCube[i]->SetModel(model2);
    }

    for (int i = 0; i < 100; i++)
    {
        PartCube[i] = nullptr;
        PartCube[i] = new Enemy;
        PartCube[i]->Initialize();
        PartCube[i]->SetPosition({ 100.0f + 1.0f * i,5.0f,20.0f });
        PartCube[i]->SetScale({ 0.5f,0.5f,0.5f });
        PartCube[i]->SetModel(model2);
    }


    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ -20.0f,-1.0f,-50.0f });
    floor->SetScale({ 10.0f,0.5f,10.0f });
    floor->SetModel(modelfloor);

    floor2 = new FBXobj3d;
    floor2->Initialize();
    floor2->SetPosition({ -11.3f,0.5f,0.2f });
    floor2->SetModel(modelfloor);
         
    wall = new FBXobj3d;
    wall->Initialize();
    wall->SetPosition({ -30.0f,50.0f,100.0f });
    wall->SetScale({ 200.0f,10.0f,0.5f });
    wall->SetRotation({ 0.0f,0.0f,0.0f });
    wall->SetModel(modelwall);

    wall2 = new FBXobj3d;
    wall2->Initialize();
    wall2->SetPosition({ -30.0f,50.0f,100.0f });
    wall2->SetScale({ 20.0f,10.0f,1.0f });
    wall2->SetRotation({ 0.0f,90.0f,0.0f });
    wall2->SetModel(modelwall);

    wall3 = new FBXobj3d;
    wall3->Initialize();
    wall3->SetPosition({ 75.0f,50.0f,100.0f });
    wall3->SetScale({ 20.0f,10.0f,1.0f });
    wall3->SetRotation({ 0.0f,90.0f,0.0f });
    wall3->SetModel(modelwall);


    ballet = new Pbullet;
    ballet->Initialize();
    ballet->SetPosition({ 500.0f,5.0f,0.0f });
    ballet->SetScale({ 1.0f,1.0f,1.0f });
    ballet->SetModel(modelballet);
    //ballet->SetCollider(new SphereCollider(XMVECTOR{ 0,0,0,0 }, 3.0f));
    
    

    player = new Player(ballet);
    player->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);
    player->PlayerInitialize(this->input);
    

    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[

    Otin->PlayAnimation();
    //cube->PlayAnimation();



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

    //cube->SetPosition({movex,movey,movez});


    Otin->Update();
    cube->Update();
    for (int i = 0; i < 8; i++)
    {
        DivCube[i]->Update();
    }

    for (int i = 0; i < 100; i++)
    {
        PartCube[i]->Update();
    }
    floor->Update();
    floor2->Update();
    wall->Update();
    wall2->Update();
    wall3->Update();
    ballet->Update();

    camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);
   //player->CurrentUpdate();
    //player->Update(WindowsApp::window_width, WindowsApp::window_height);

    //�Q�[���{��
    
    player->PlayerUpdate();

    /*if(input->PushKey(DIK_E))
    {
        for (int i = 0; i < 8; i++)
        {
            DivCube[i]->EnemyUpdate();
        }
    }*/

    ////���ׂĂ̏Փ˂��`�F�b�N
    collisionManager->CheckAllCollisions();
    XMFLOAT3 bulpos = ballet->GetPos();
    XMFLOAT3 epos = cube->GetPos();

    //�ʂƓG�̓����蔻��
    XMVECTOR position_sub = XMVectorSet(
        bulpos.x - epos.x,
        bulpos.y - epos.y,
        bulpos.z - epos.z,
        0
    );

    position_sub = XMVector3Length(position_sub);
    float distance = position_sub.m128_f32[0];
    //�������Ă���
    if (distance <= 1.2f + 1.2f)
    {

        for (int i = 0; i < 100; i++)
        {
            srand(rand());
            int pcount = rand() % 10 + 1;

            eVel[i].m128_f32[0] = (float)rand() / RAND_MAX;
            eVel[i].m128_f32[1] = (float)rand() / RAND_MAX;
            eVel[i].m128_f32[2] = (float)rand() / RAND_MAX;

            //������ݒ�
            if (pcount >= 4)
            {
                eVel[i].m128_f32[0] *= -1;
            }
            if (pcount % 2 == 0)
            {
                eVel[i].m128_f32[1] *= -1;
            }
            if (pcount % 2 == 1)
            {
                eVel[i].m128_f32[2] *= -1;
            }

            PartCube[i]->Enemycol(cube->GetPos(),eVel[i]);
        }

        cube->EnemyDeleate();   
    }

    /*for (int i = 0; i < 8; i++)
    {
        DivCube[i]->EnemyUpdate();
    }*/

    for (int i = 0; i < 100; i++)
    {
        PartCube[i]->EnemyUpdate();
    }

    if (resetflag==1)
    {
        for (int i = 0; i < 100; i++)
        {
            /*camera->SetEye({ 0,5,0 });
            camera->SetTarget({ 0,5,0 });
            camera->SetUp({ 0,1,0 });
            camera->SetRoatation({ 0,0,0 });*/
            PartCube[i]->SetPosition({ 100.0f + 1.0f * i,5.0f,20.0f });
            PartCube[i]->colReset();
        }
        cube->SetPosition({ 5.0f,5.0f,20.0f });
        resetflag = 0;
    }

    
    //debugText->Print("Hello,DirectX!!", 200, 100);

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
    Otin->Draw(cmdList);//otintin
    cube->Draw(cmdList);//cube
    /*for (int i = 0; i < 8; i++)
    {
        DivCube[i]->Draw(cmdList);
    }*/

    for (int i = 0; i < 100; i++)
    {
        PartCube[i]->Draw(cmdList);
    }
    floor->Draw(cmdList);
   // floor2->Draw(cmdList);
    wall->Draw(cmdList);
    wall2->Draw(cmdList);
    wall3->Draw(cmdList);
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

    delete Otin;
    delete model1;
    delete cube;
    delete model2;
}
