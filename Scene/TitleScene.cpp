#include "TitleScene.h"
#include"SceneManager.h"

class GameScene;

template<>
BaseScene* BaseScene::makeScene<TitleScene>() {
    return new TitleScene();
}

void TitleScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //ポインタ置き場
    this->dxCommon = dxcommon;
    this->input = input;
    this->spriteCommon = spritecommon;
    this->Windows = windows;

    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    spriteCommon->LoadTexture(2, L"Resources/title.png");

    title = Sprite::Create(spriteCommon, 2);
    title->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    title->TransferVertexBuffer();

}

void TitleScene::Update()
{
    if (titleflag == true)
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
            spritesize.x -= 1.0f;
            spritesize.y -= 1.0f;
        }
        else
        {
            spritesize.x +=1.0f;
            spritesize.y +=1.0f;
        }

        //title->SetRotation(spriteangle);
        title->SetSize(spritesize);
        title->TransferVertexBuffer();
        title->Update();
        if (input->TriggerKey(DIK_SPACE))
        {
            playscene = 1;
            spritesize = { 1280,720 };
            transfrag = true;
            titleflag = false;
            //次のシーンを生成
            
            BaseScene* scene = makeScene<GameScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);

        }
    }
   
}

void TitleScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    //スプライト描画前処理
    spriteCommon->PreDraw();
    if (titleflag == true)
    {
        title->Draw();
    }
}

void TitleScene::Finalize()
{

}
