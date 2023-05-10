#include"ClearScene.h"
#include"SceneManager.h"

void ClearScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //ポインタ置き場
    this->dxCommon = dxcommon;
    this->input = input;
    this->spriteCommon = spritecommon;
    this->Windows = windows;

    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    spriteCommon->LoadTexture(4, L"Resources/clear.png");


    clear = Sprite::Create(spriteCommon, 4);
    clear->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    clear->TransferVertexBuffer();
}

void ClearScene::Update()
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
            spritesize.x -= 0.4f;
            spritesize.y -= 0.3f;
        }
        else
        {
            spritesize.x += 0.4f;
            spritesize.y += 0.3f;
        }

        //title->SetRotation(spriteangle);
        clear->SetSize(spritesize);
        clear->TransferVertexBuffer();
        clear->Update();

        if (input->TriggerKey(DIK_SPACE))
        {
            spritesize = { 1280,720 };
            transfrag = true;
            //次のシーンを生成
           // BaseScene* scene = new GameScene();
            //シーン切り替え
            //sceneManager->NextScene(scene);
        }
}
