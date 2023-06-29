#include"StageData.h"
#include<fstream>
#include <iomanip>
#include"GameScene.h"




StageData::StageData()
{
    //gamescene = new GameScene;
}

void StageData::LoadEnemyDataS1()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/EnemyDataS1.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    enemyDataS1 << file.rdbuf();

    //�t�@�C�������
    //�擪�ɖ߂�
    file.close();
    file.clear();
    file.seekg(0, std::ios::beg);


}

void StageData::LoadWallDataS1()
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

void StageData::LoadEnemyDataS2()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/EnemyDataS2.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    enemyDataS2 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void StageData::LoadWallDataS2()
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

void StageData::LoadEnemyDataS3()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/EnemyDataS3.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    enemyDataS3 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void StageData::LoadWallDataS3()
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

void StageData::LoadEnemyDataS4()
{
    //�t�@�C�����J��
    std::ifstream file;
    file.open(L"Resources/EnemyDataS4.csv");
    assert(file.is_open());

    //�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
    enemyDataS4 << file.rdbuf();

    //�t�@�C�������
    file.close();
}

void StageData::LoadWallDataS4()
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

void StageData::SwapEnemyDataS1() {

    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����

    gamescene = new GameScene;

    //1�s���̕����������ϐ�
    std::string line;

    //�G�̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    int modelname;//���f���̎w��
    float r;//�R���C�_�[�̔��a�w��
    bool mod;//�G�̎�ނ̎w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;
    int count = 0;

    //�R�}���h���s���[�v
    while (getline(enemyDataS1, line))
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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��)�̔��a�w��
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //�G�̎�ގw��
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            
            enemypos.push_back(std::move(pos));
            enemyscale.push_back(std::move(scale));
            enemymodelname.push_back(std::move(modelname));
            enemyr.push_back(std::move(r));
            enemymod.push_back(std::move(mod));

            count++;
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS1()
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
    int count = 0;

   
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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

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

        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            
            wallpos.push_back(std::move(pos));
            wallscale.push_back(std::move(scale));
            wallrotation.push_back(std::move(rotation));
            wallmodelname.push_back(std::move(modelname));
            wallr.push_back(std::move(r));

            count++;
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }

    }
    wallNum = count;
}

void StageData::SwapEnemyDataS2() {

    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����


    //1�s���̕����������ϐ�
    std::string line;

    //�G�̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    int modelname;//���f���̎w��
    float r;//�R���C�_�[�̔��a�w��
    bool mod;//�G�̎�ނ̎w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;
    int count = 0;

    //�G��list�ǉ�
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();


    //�R�}���h���s���[�v
    while (getline(enemyDataS2, line))
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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��)�̔��a�w��
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //�G�̎�ގw��
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());

            enemypos.push_back(std::move(pos));
            enemyscale.push_back(std::move(scale));
            enemymodelname.push_back(std::move(modelname));
            enemyr.push_back(std::move(r));
            enemymod.push_back(std::move(mod));
            count++;
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS2()
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
    int count = 0;

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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

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

        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            
            wallpos.push_back(std::move(pos));
            wallscale.push_back(std::move(scale));
            wallrotation.push_back(std::move(rotation));
            wallmodelname.push_back(std::move(modelname));
            wallr.push_back(std::move(r));
            count++;
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

        }

    }
    wallNum = count;
}

void StageData::SwapEnemyDataS3() {

    //csv�ɃX�e�[�W�w��̃R�}���h�����
    //�ǂݎ���ăX�e�[�W���Ƃ�pushback�ύX����


    //1�s���̕����������ϐ�
    std::string line;

    //�G�̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    int modelname;//���f���̎w��
    float r;//�R���C�_�[�̔��a�w��
    bool mod;//�G�̎�ނ̎w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;
    int count = 0;

    //�G��list�ǉ�
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();


    //�R�}���h���s���[�v
    while (getline(enemyDataS3, line))
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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��)�̔��a�w��
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //�G�̎�ގw��
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());

            enemypos.push_back(std::move(pos));
            enemyscale.push_back(std::move(scale));
            enemymodelname.push_back(std::move(modelname));
            enemyr.push_back(std::move(r));
            enemymod.push_back(std::move(mod));
            count++;
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS3()
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
    int count = 0;

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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

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

        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            wallpos.push_back(std::move(pos));
            wallscale.push_back(std::move(scale));
            wallrotation.push_back(std::move(rotation));
            wallmodelname.push_back(std::move(modelname));
            wallr.push_back(std::move(r));
            count++;
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

        }

    }
    wallNum = count;
}

void StageData::SwapEnemyDataS4() {

    //1�s���̕����������ϐ�
    std::string line;

    //�G�̏��
    XMFLOAT3 pos{};//���W
    XMFLOAT3 scale{};//�X�P�[��
    int modelname;//���f���̎w��
    float r;//�R���C�_�[�̔��a�w��
    bool mod;//�G�̎�ނ̎w��
    int stage;//�X�e�[�W�̎w��
    int nextflag = 0;
    int count = 0;

    //�G��list�ǉ�
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();



    //�R�}���h���s���[�v
    while (getline(enemyDataS4, line))
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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //�R���C�_�[(��)�̔��a�w��
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //�G�̎�ގw��
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            count++;
            gamescene->SwapEnemyData(pos, scale, modelname, r, mod);

        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS4()
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

        }
        else if (word.find("MODEL") == 0)
        {
            //���f���̎w��
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

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

        }
        else if (word.find("STAGE") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            //gamescene->SwapWallData(pos, scale, rotation, modelname, r, nextflag);
            wallpos.push_back(std::move(pos));
            wallscale.push_back(std::move(scale));
            wallrotation.push_back(std::move(rotation));
            wallmodelname.push_back(std::move(modelname));
            wallr.push_back(std::move(r));
        }
        else if (word.find("NEXT") == 0)
        {
            //�X�e�[�W�̎w��
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

        }

    }
}


void StageData::InsertData
(int& stagenum,int& tuto, int& enemynum, int& wallnum,
    std::vector<XMFLOAT3>& epos, std::vector<XMFLOAT3>& escale, std::vector<int>& ename, std::vector<float>& er, std::vector<bool>& emod,
    std::vector<XMFLOAT3>& wpos, std::vector<XMFLOAT3>& wscale, std::vector<XMFLOAT3>& wrotation, std::vector<int>& wname, std::vector<XMFLOAT3>& wr)
{

    if (stagenum==1)
    {
        LoadEnemyDataS1();
        SwapEnemyDataS1();
        LoadWallDataS1();
        SwapWallDataS1();

        epos = enemypos;
        escale = enemyscale;
        ename = enemymodelname;
        er = enemyr;
        emod = enemymod;

        wpos = wallpos;
        wscale = wallscale;
        wrotation = wallrotation;
        wname = wallmodelname;
        wr = wallr;

        enemynum = GetenemyNum();
        wallnum = wallNum;
        tuto = 3;
    }
    else if (stagenum == 2)
    {
        LoadEnemyDataS2();
        SwapEnemyDataS2();
        LoadWallDataS2();
        SwapWallDataS2();

        epos = enemypos;
        escale = enemyscale;
        ename = enemymodelname;
        er = enemyr;
        emod = enemymod;

        wpos = wallpos;
        wscale = wallscale;
        wrotation = wallrotation;
        wname = wallmodelname;
        wr = wallr;

        enemynum = enemyNum;
        wallnum = wallNum;
        tuto = 3;
    }
    else if (stagenum == 3)
    {
        LoadEnemyDataS3();
        SwapEnemyDataS3();
        LoadWallDataS3();
        SwapWallDataS3();

        epos = enemypos;
        escale = enemyscale;
        ename = enemymodelname;
        er = enemyr;
        emod = enemymod;

        wpos = wallpos;
        wscale = wallscale;
        wrotation = wallrotation;
        wname = wallmodelname;
        wr = wallr;

        enemynum = enemyNum;
        wallnum = wallNum;
        tuto = 2;
    }
}