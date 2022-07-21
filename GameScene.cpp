#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>


using namespace DirectX;

void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon)
{
    //�|�C���^�u����
    
    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;

    //�J��������
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height);


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

    

    //OBJ����
    //model* Model = model::LoadFromOBJ("skydome");
    //3d�I�u�W�F�N�g����
    //Object3d* object3d = Object3d::Create();
    //���f���R�Â�
    object3d->SetModel(Model);

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
    model2 = FbxLoader::GetInstance()->LoadModelFromFile("cube");

    Otin = new FBXobj3d;
    Otin->Initialize();
    Otin->SetPosition({ 0.0f,0.0f,0.0f });
    Otin->SetModel(model1);

    cube = new FBXobj3d;
    cube->Initialize();
    cube->SetPosition({ 10.0f,0.0f,0.0f });
    cube->SetModel(model1);

    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[

    Otin->PlayAnimation();
    cube->PlayAnimation();
}

void GameScene::Update()
{

    //�X�v���C�g�X�V
    //obj�X�V
    object3d->Update();
    //FBX�X�V
    Otin->Update();
    cube->Update();

    

    if (input->PushclickLeft())
    {
        input->Mousemove();
        adsVelocity.x = input->GetVelx();
        adsVelocity.y = input->GetVely();
        camera->SetRoatation(adsVelocity);
    }
    else
    {
        adsVelocity.x = 0;
        adsVelocity.y = 0;
    }

    //����
    if (input->PushKey(DIK_A)) Velocity.x = 0.1f;
    else
    {
        if (input->PushKey(DIK_D)) Velocity.x = -0.1f;
    }
    
    if (!input->PushKey(DIK_A) && !input->PushKey(DIK_D)) Velocity.x = 0;

    if (input->PushKey(DIK_S)) Velocity.z = 0.1f;
    else
    {
        if (input->PushKey(DIK_W)) Velocity.z = -0.1f;
    }

    if (!input->PushKey(DIK_W) && !input->PushKey(DIK_S)) Velocity.z = 0;

    camera->MoveVector(Velocity);

    camera->MoveTarget(adsVelocity);

    camera->Update(WindowsApp::window_width, WindowsApp::window_height);

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
    //object3d->Draw();

    //FBX�`��
    Otin->Draw(cmdList);//otintin
    cube->Draw(cmdList);//cube

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();

    //obj�̕`��㏈��
    Object3d::PostDraw();
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
