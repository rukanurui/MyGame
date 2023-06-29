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
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS1.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS1 << file.rdbuf();

    //ファイルを閉じる
    //先頭に戻る
    file.close();
    file.clear();
    file.seekg(0, std::ios::beg);


}

void StageData::LoadWallDataS1()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS1.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS1 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::LoadEnemyDataS2()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS2.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS2 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::LoadWallDataS2()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS2.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS2 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::LoadEnemyDataS3()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS3.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS3 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::LoadWallDataS3()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS3.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS3 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::LoadEnemyDataS4()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/EnemyDataS4.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    enemyDataS4 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::LoadWallDataS4()
{
    //ファイルを開く
    std::ifstream file;
    file.open(L"Resources/WallDataS4.csv");
    assert(file.is_open());

    //ファイルの内容を文字列ストリームにコピー
    wallDataS4 << file.rdbuf();

    //ファイルを閉じる
    file.close();
}

void StageData::SwapEnemyDataS1() {

    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する

    gamescene = new GameScene;

    //1行分の文字列を入れる変数
    std::string line;

    //敵の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    int modelname;//モデルの指定
    float r;//コライダーの半径指定
    bool mod;//敵の種類の指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

    //コマンド実行ループ
    while (getline(enemyDataS1, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());


        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(球)の半径指定
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //敵の種類指定
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS1()
{
    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //壁の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    XMFLOAT3 rotation{};//ローテーション
    int modelname;//モデルの指定
    XMFLOAT3 r;//コライダーの半径指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

   
    //コマンド実行ループ
    while (getline(wallDataS1, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("ROTAT") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(矩形)の半径指定
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }

    }
    wallNum = count;
}

void StageData::SwapEnemyDataS2() {

    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //敵の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    int modelname;//モデルの指定
    float r;//コライダーの半径指定
    bool mod;//敵の種類の指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

    //敵のlist追加
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();


    //コマンド実行ループ
    while (getline(enemyDataS2, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());


        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(球)の半径指定
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //敵の種類指定
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS2()
{
    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //壁の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    XMFLOAT3 rotation{};//ローテーション
    int modelname;//モデルの指定
    XMFLOAT3 r;//コライダーの半径指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

    //壁のlist追加
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //コマンド実行ループ
    while (getline(wallDataS2, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("ROTAT") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(矩形)の半径指定
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

        }

    }
    wallNum = count;
}

void StageData::SwapEnemyDataS3() {

    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //敵の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    int modelname;//モデルの指定
    float r;//コライダーの半径指定
    bool mod;//敵の種類の指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

    //敵のlist追加
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();


    //コマンド実行ループ
    while (getline(enemyDataS3, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());


        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(球)の半径指定
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //敵の種類指定
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS3()
{
    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //壁の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    XMFLOAT3 rotation{};//ローテーション
    int modelname;//モデルの指定
    XMFLOAT3 r;//コライダーの半径指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

    //壁のlist追加
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //コマンド実行ループ
    while (getline(wallDataS3, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("ROTAT") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(矩形)の半径指定
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());

        }

    }
    wallNum = count;
}

void StageData::SwapEnemyDataS4() {

    //1行分の文字列を入れる変数
    std::string line;

    //敵の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    int modelname;//モデルの指定
    float r;//コライダーの半径指定
    bool mod;//敵の種類の指定
    int stage;//ステージの指定
    int nextflag = 0;
    int count = 0;

    //敵のlist追加
    std::unique_ptr<Enemy>newenemy = std::make_unique<Enemy>();
    newenemy->Initialize();



    //コマンド実行ループ
    while (getline(enemyDataS4, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());


        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(球)の半径指定
            getline(line_stream, word, ',');
            r = (float)std::atof(word.c_str());

        }
        else if (word.find("SHOT") == 0)
        {
            //敵の種類指定
            getline(line_stream, word, ',');
            mod = (float)std::atof(word.c_str());
        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
            getline(line_stream, word, ',');
            stage = (float)std::atof(word.c_str());
            count++;
            gamescene->SwapEnemyData(pos, scale, modelname, r, mod);

        }
        else if (word.find("NEXT") == 0)
        {
            //ステージの指定
            getline(line_stream, word, ',');
            nextflag = (float)std::atof(word.c_str());
        }
    }
    enemyNum = count;
}

void StageData::SwapWallDataS4()
{
    //csvにステージ指定のコマンド入れる
    //読み取ってステージごとにpushback変更する


    //1行分の文字列を入れる変数
    std::string line;

    //壁の情報
    XMFLOAT3 pos{};//座標
    XMFLOAT3 scale{};//スケール
    XMFLOAT3 rotation{};//ローテーション
    int modelname;//モデルの指定
    XMFLOAT3 r;//コライダーの半径指定
    int stage;//ステージの指定
    int nextflag = 0;

    //壁のlist追加
    std::unique_ptr<Wall>newwall = std::make_unique<Wall>();
    newwall->Initialize();

    //コマンド実行ループ
    while (getline(wallDataS4, line))
    {

        //1行分の文字列をストリームに変換して解析しやすくなる
        std::istringstream line_stream(line);

        std::string word;
        //,区切りで行の先頭部分を取得
        getline(line_stream, word, ',');

        // "//"から始まる行はコメントアウト
        if (word.find("//") == 0)
        {
            //コメント行を飛ばす
            continue;
        }


        if (word.find("POSITION") == 0)
        {
            //x座標
            getline(line_stream, word, ',');
            pos.x = (float)std::atof(word.c_str());

            //y座標
            getline(line_stream, word, ',');
            pos.y = (float)std::atof(word.c_str());

            //z座標
            getline(line_stream, word, ',');
            pos.z = (float)std::atof(word.c_str());

        }
        else if (word.find("SCALE") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            scale.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            scale.z = (float)std::atof(word.c_str());

        }
        else if (word.find("ROTAT") == 0)
        {
            //xのスケール
            getline(line_stream, word, ',');
            rotation.x = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.y = (float)std::atof(word.c_str());

            //xのスケール
            getline(line_stream, word, ',');
            rotation.z = (float)std::atof(word.c_str());

        }
        else if (word.find("MODEL") == 0)
        {
            //モデルの指定
            getline(line_stream, word, ',');
            modelname = (float)std::atof(word.c_str());

        }
        else if (word.find("COLLIDER") == 0)
        {
            //コライダー(矩形)の半径指定
            getline(line_stream, word, ',');
            r.x = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.y = (float)std::atof(word.c_str());

            getline(line_stream, word, ',');
            r.z = (float)std::atof(word.c_str());

        }
        else if (word.find("STAGE") == 0)
        {
            //ステージの指定
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
            //ステージの指定
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