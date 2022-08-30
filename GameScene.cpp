#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>


using namespace DirectX;

void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon,WindowsApp*windows)
{
    //�|�C���^�u����
    
    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->windows = windows;



    //�J��������
    camera = new Camera(this->input,this->windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height,this->input);


#pragma region �`�揉��������


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

    
    //�X�v���C�g�̐���


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

    cube = new FBXobj3d;
    cube->Initialize();
    cube->SetPosition({ 10.0f,0.0f,10.0f });
    cube->SetModel(model2);

    floor = new FBXobj3d;
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetModel(modelfloor);

    floor2 = new FBXobj3d;
    floor2->Initialize();
    floor2->SetPosition({ -11.3f,0.5f,0.2f });
    floor2->SetModel(modelfloor);
         
    wall = new FBXobj3d;
    wall->Initialize();
    wall->SetPosition({ 3.0f,18.0f,18.0f });
    wall->SetModel(modelwall);

    wall2 = new FBXobj3d;
    wall2->Initialize();
    wall2->SetPosition({ -10.0f,18.0f,18.0f });
    wall2->SetModel(modelwall);

    ballet = new FBXobj3d;
    ballet->Initialize();
    ballet->SetPosition({ 0.0f,5.0f,0.0f });
    ballet->SetModel(modelballet);

    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[

    Otin->PlayAnimation();
    //cube->PlayAnimation();
}

void GameScene::Update()
{

    // �}�E�X�̓��͂��擾
    Input::MouseMove mouseMove = input->GetMouseMove();

    CurretmouseX = mouseMove.lX;
    CurretmouseY = mouseMove.lY;

    camera->SetmouseX(CurretmouseX);
    camera->SetmouseY(CurretmouseY);

    if (bulflag == 0)
    {
        bulpos = camera->GetEye();
        bulpos.z -= 1.0f;
    }

    //�X�v���C�g�X�V
    
    //FBX�X�V

    //cube->SetPosition({movex,movey,movez});

    Otin->Update();
    cube->Update();
    floor->Update();
    floor2->Update();
    wall->Update();
    wall2->Update();
    ballet->Update();

    camera->CurrentUpdate();
    camera->Update(WindowsApp::window_width, WindowsApp::window_height);

    //�Q�[���{��
    if (input->PushKey(DIK_SPACE))
    {
        bulflag = 1;
    }

    if (bulflag==1)
    {
        bulpos.z += 0.1f;
        ballet->SetPosition(bulpos);
        if (bulpos.z >= 20)
        {
           bulflag = 0;
        }
    }

}

void GameScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    //obj�`��O����
    Object3d::PreDraw(dxCommon->GetCommandList());
    // �X�v���C�g�`��O����
    //spriteCommon->PreDraw();

    //obj�A�X�v���C�g�̕`��
    
    //obj�̕`��㏈��
    Object3d::PostDraw();

    //FBX�`��
    Otin->Draw(cmdList);//otintin
    cube->Draw(cmdList);//cube
    floor->Draw(cmdList);
   // floor2->Draw(cmdList);
    wall->Draw(cmdList);
    //wall2->Draw(cmdList);

    if (bulflag==1) ballet->Draw(cmdList);

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();
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
