#include"ClearScene.h"
#include"SceneManager.h"
#include<fstream>

class GameScene;
class TitleScene;

template<>
BaseScene* BaseScene::makeScene<ClearScene>() {
    return new ClearScene();
}

void ClearScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //�|�C���^�u����
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

    modelwall = FbxLoader::GetInstance()->LoadModelFromFile("colorwall");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");
    //�n�`3d�I�u�W�F�N�g
    //��
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

    if (playscene==2)
    {
        LoadWallDataS1();
        SwapWallDataS1();
    }

    if (playscene == 5)
    {
        LoadWallDataS2();
        SwapWallDataS2();
    }

    if (playscene == 6)
    {
        LoadWallDataS3();
        SwapWallDataS3();
    }

    if (playscene == 7)
    {
        LoadWallDataS4();
        SwapWallDataS4();
    }

}

void ClearScene::LoadWallDataS1()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/WallDataS1.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    wallDataS1 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void ClearScene::LoadWallDataS2()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/WallDataS2.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    wallDataS2 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void ClearScene::LoadWallDataS3()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/WallDataS3.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    wallDataS3 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void ClearScene::LoadWallDataS4()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/WallDataS4.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    wallDataS4 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void ClearScene::SwapWallDataS1()
{
    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����


    //1�s���̕����������ϐ�
    std::string line;

    //�ǂ̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    XMFLOAT3 rotation{};//���[�e�[�V����
    int modelname;//���f���̎w��
    XMFLOAT3 r;//�R���C�_�[�̔��a�w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;

    //�ǂ�list�ǉ�
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //�R�}���h���s���[�v
    while (getline(wallDataS1, line))
    {

        //1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷���Ȃ�
        std::istringstream line_stream(line);

        std::string word;
        //,��؂�ōs�̐擪�������擾
        getline(line_stream, word, ',');

        // "//"����n�܂�s�̓R�����g�A�E�g
        if (word.find("//") == 0)
        {
            //�R�����g�s���΂�
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x���W
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y���W
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z���W
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

            newwall->SetPosition({ pos.x,pos.y,pos.z });

        }
        else if (word.find("SCALE") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

            newwall->SetScale({ scale.x,scale.y,scale.z });
        }
        else if (word.find("ROTAT") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

            newwall->SetRotation({ rotation.x,rotation.y,rotation.z });
        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname == 1)
            {
                newwall->SetModel(modelwall);
            }

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��`)�̔��a�w��
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

            newwall->SetCollider(new BoxCollider(XMVECTOR{ r.x,r.y,r.z,0 }, 1.0f));
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            if (stage == 1)
            {
                newwall->WallInitialize();
                Stage1Walls.push_back(std::move(newwall));
            }
            else if (stage == 2)
            {
                newwall->WallInitialize();
                Stage2Walls.push_back(std::move(newwall));
            }
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

            if (nextflag == 1)
            {
                newwall = std::make_unique<Wall>();
                newwall->Initialize();
            }

        }

    }
}

void ClearScene::SwapWallDataS2()
{
    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����


    //1�s���̕����������ϐ�
    std::string line;

    //�ǂ̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    XMFLOAT3 rotation{};//���[�e�[�V����
    int modelname;//���f���̎w��
    XMFLOAT3 r;//�R���C�_�[�̔��a�w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;

    //�ǂ�list�ǉ�
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //�R�}���h���s���[�v
    while (getline(wallDataS2, line))
    {

        //1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷���Ȃ�
        std::istringstream line_stream(line);

        std::string word;
        //,��؂�ōs�̐擪�������擾
        getline(line_stream, word, ',');

        // "//"����n�܂�s�̓R�����g�A�E�g
        if (word.find("//") == 0)
        {
            //�R�����g�s���΂�
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x���W
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y���W
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z���W
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

            newwall->SetPosition({ pos.x,pos.y,pos.z });

        }
        else if (word.find("SCALE") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

            newwall->SetScale({ scale.x,scale.y,scale.z });
        }
        else if (word.find("ROTAT") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

            newwall->SetRotation({ rotation.x,rotation.y,rotation.z });
        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname == 1)
            {
                newwall->SetModel(modelwall);
            }

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��`)�̔��a�w��
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

            newwall->SetCollider(new BoxCollider(XMVECTOR{ r.x,r.y,r.z,0 }, 1.0f));
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            if (stage == 1)
            {
                newwall->WallInitialize();
                Stage1Walls.push_back(std::move(newwall));
            }
            else if (stage == 2)
            {
                newwall->WallInitialize();
                Stage2Walls.push_back(std::move(newwall));
            }
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

            if (nextflag == 1)
            {
                newwall = std::make_unique<Wall>();
                newwall->Initialize();
            }

        }

    }
}

void ClearScene::SwapWallDataS3()
{
    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����


    //1�s���̕����������ϐ�
    std::string line;

    //�ǂ̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    XMFLOAT3 rotation{};//���[�e�[�V����
    int modelname;//���f���̎w��
    XMFLOAT3 r;//�R���C�_�[�̔��a�w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;

    //�ǂ�list�ǉ�
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //�R�}���h���s���[�v
    while (getline(wallDataS3, line))
    {

        //1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷���Ȃ�
        std::istringstream line_stream(line);

        std::string word;
        //,��؂�ōs�̐擪�������擾
        getline(line_stream, word, ',');

        // "//"����n�܂�s�̓R�����g�A�E�g
        if (word.find("//") == 0)
        {
            //�R�����g�s���΂�
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x���W
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y���W
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z���W
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

            newwall->SetPosition({ pos.x,pos.y,pos.z });

        }
        else if (word.find("SCALE") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

            newwall->SetScale({ scale.x,scale.y,scale.z });
        }
        else if (word.find("ROTAT") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

            newwall->SetRotation({ rotation.x,rotation.y,rotation.z });
        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname == 1)
            {
                newwall->SetModel(modelwall);
            }

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��`)�̔��a�w��
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

            newwall->SetCollider(new BoxCollider(XMVECTOR{ r.x,r.y,r.z,0 }, 1.0f));
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            if (stage == 3)
            {
                newwall->WallInitialize();
                Stage3Walls.push_back(std::move(newwall));
            }
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

            if (nextflag == 1)
            {
                newwall = std::make_unique<Wall>();
                newwall->Initialize();
            }

        }

    }
}

void ClearScene::SwapWallDataS4()
{
    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����


    //1�s���̕����������ϐ�
    std::string line;

    //�ǂ̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    XMFLOAT3 rotation{};//���[�e�[�V����
    int modelname;//���f���̎w��
    XMFLOAT3 r;//�R���C�_�[�̔��a�w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;

    //�ǂ�list�ǉ�
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //�R�}���h���s���[�v
    while (getline(wallDataS4, line))
    {

        //1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷���Ȃ�
        std::istringstream line_stream(line);

        std::string word;
        //,��؂�ōs�̐擪�������擾
        getline(line_stream, word, ',');

        // "//"����n�܂�s�̓R�����g�A�E�g
        if (word.find("//") == 0)
        {
            //�R�����g�s���΂�
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x���W
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y���W
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z���W
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

            newwall->SetPosition({ pos.x,pos.y,pos.z });

        }
        else if (word.find("SCALE") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

            newwall->SetScale({ scale.x,scale.y,scale.z });
        }
        else if (word.find("ROTAT") == 0)
        {
            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //x�̃X�P�[��
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

            newwall->SetRotation({ rotation.x,rotation.y,rotation.z });
        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

            if (modelname == 1)
            {
                newwall->SetModel(modelwall);
            }

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��`)�̔��a�w��
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

            newwall->SetCollider(new BoxCollider(XMVECTOR{ r.x,r.y,r.z,0 }, 1.0f));
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            if (stage == 4)
            {
                newwall->WallInitialize();
                Stage4Walls.push_back(std::move(newwall));
            }
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

            if (nextflag == 1)
            {
                newwall = std::make_unique<Wall>();
                newwall->Initialize();
            }

        }

    }
}


void ClearScene::Update()
{  

    if (spritesize.x >= 1280)
    {
        transfrag = true;
    }
    if (spritesize.x <= 800)
    {
        transfrag = false;
    }

    if (transfrag == true)
    {
        spritesize.x -= 4.0f;
        spritesize.y -= 3.0f;
    }
    else
    {
        spritesize.x += 4.0f;
        spritesize.y += 3.0f;
    }

    clear->SetSize(spritesize);

    clear->TransferVertexBuffer();

    clear->Update();

    //FBX�X�V
    floor->Update();

    if (playscene == 2)
    {
        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Update();
        }

        if (input->PushKey(DIK_SPACE))
        {
            playscene = 5;
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<GameScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            //���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
            sceneManager->SetplayScene(playscene);
            return;
        }
    }

    if (playscene == 5)
    {

        for (std::unique_ptr<Wall>& wall : Stage2Walls)
        {
            wall->Update();
        }

        if (input->PushKey(DIK_SPACE))
        {
            playscene = 6;
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<GameScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            //���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
            sceneManager->SetplayScene(playscene);
            return;
        }
    }

    if (playscene == 6)
    {

        for (std::unique_ptr<Wall>& wall : Stage3Walls)
        {
            wall->Update();
        }

        if (input->PushKey(DIK_SPACE))
        {
            playscene = 7;
            ////���̃V�[���𐶐�
            //BaseScene* scene = makeScene<GameScene>();
            ////�V�[���؂�ւ�
            //sceneManager->NextScene(scene);
            ////���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
            //sceneManager->SetplayScene(playscene);

            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<TitleScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            return;

        }
    }

    if (playscene == 7)
    {

        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Update();
        }

        if (input->PushKey(DIK_SPACE))
        {
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<TitleScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            return;
        }
    }

}

void ClearScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

    if (playscene == 2)
    {
        for (std::unique_ptr<Wall>& wall : Stage1Walls)
        {
            wall->Draw(cmdList);
        }
    }

    if (playscene == 5)
    {

        for (std::unique_ptr<Wall>& wall : Stage2Walls)
        {
            wall->Draw(cmdList);
        }
    }

    if (playscene == 6)
    {
        for (std::unique_ptr<Wall>& wall : Stage3Walls)
        {
            wall->Draw(cmdList);
        }
    }

    if (playscene == 7)
    {
        for (std::unique_ptr<Wall>& wall : Stage4Walls)
        {
            wall->Draw(cmdList);
        }
    }

    floor->Draw(cmdList);

    //�X�v���C�g�`��O����
    spriteCommon->PreDraw();
    clear->Draw();
    
}

void ClearScene::Finalize()
{
    /*delete clear;
    delete Windows;
    delete input;
    delete dxCommon;
    delete spriteCommon;
    delete modelfloor;
    delete modelwall;
    delete floor;*/
    

}


