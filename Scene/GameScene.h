#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��

#include "../Engine/Input.h"

#include "../Engine/WindowsApp.h"
#include "../Engine/DXCommon.h"

#include "../3d/Object3d.h"
#include "../3d/model.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include"../2d/PostEffect.h"
#include "../2d/DebugText.h"
#include "../Engine/Audio.h"

#include "fbxsdk.h"
#include "../3d/FbxLoader.h"
#include "../3d/FBXobj3d.h"
#include "../3d/Modelfbx.h"

#include "../Engine/Camera.h"
#include"../Player/Player.h"
#include"../Collider/PlayerCol.h"

#include"../Enemy/Enemy.h"
#include"../3d/Wall.h"

#include <memory>
#include <list>

#include"BaseScene.h"
#include"TransEffect.h"

#include"StageData.h"




class CollisionManager;


class GameScene : public BaseScene
{
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�����o�֐�

	//������
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;
	
	//�X�V
	void Update()override;
	//�V�[������
	const int& GettutoScene() { return tutoscene; }

	//�V�[���J�ڏ���
	//void transrationScene();
	//�c�e����getter
	const int& Getmagazin() { return magazin; };
	//�e�������Ă��邩��getter
	const bool& Gethave() { return have; };
	//�`��
	void Draw()override;
	//���
	void Finalize()override;
	//�G�f�[�^�󂯎��
	void SwapEnemyData(XMFLOAT3& pos, XMFLOAT3& scale, int& modelname, float& r, bool& mod, int& stage, int& nextflag);
	//�n�`�f�[�^�󂯎��
	void SwapWallData(XMFLOAT3& pos, XMFLOAT3& scale, XMFLOAT3& rotation, int& modelname, XMFLOAT3& r,int& numcount);
	//const int& GetScene() { return scene; }

	void setepos(XMFLOAT3 pos) { this->enemypos = pos; }
	void setescale(XMFLOAT3 scale) { this->enemyscale = scale; }
	//void setepos(XMFLOAT3 pos) { this->enemypos = pos; }
	//void setepos(XMFLOAT3 pos) { this->enemypos = pos; }

	void setenemynum(int enemynum) { this->enemyNum = enemynum; }

private://�����o�ϐ�
	WindowsApp * Windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	//�Փ˃}�l�[�W���[
	CollisionManager* collisionManager = nullptr;
	StageData* stagedata = nullptr;
	
	char pla[64];

	//�X�v���C�g
	SpriteCommon* spriteCommon = nullptr;
	Sprite* crosshair = nullptr;
	Sprite* gameover = nullptr;
	Sprite* tutomove = nullptr;
	Sprite* tutomouse = nullptr;
	Sprite* tutoshot = nullptr;
	Sprite* tutorule = nullptr;
	Sprite* tutopickup = nullptr;
	Sprite* tutogunpick1 = nullptr;
	Sprite* tutogunpick2 = nullptr;
	Sprite* noammo = nullptr;
	Sprite* trans = nullptr;
	Sprite* tutostage3 = nullptr;
	Sprite* tutothrow = nullptr;
	TransEffect* transEffect = nullptr;

	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ 1280,720 };
	XMFLOAT2 movesize = { 800,300 };

	XMFLOAT2 Effectsize{ 0,0 };
	float transcount = 0;
	bool transscene = false;
	

	bool transfrag = true;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;
	bool noammoflag = false;

	//3d���f��(�n�`�Ȃ�)
	FbxModel* model2 = nullptr;
	FbxModel* modelfloor = nullptr;
	FbxModel* modelwall = nullptr;
	FbxModel* modelglasswall = nullptr;
	FBXobj3d* floor = nullptr;
	FBXobj3d* floor2 = nullptr;
	Wall* glasswallLeft = nullptr;
	Wall* glasswallForward = nullptr;

	//�I�u�W�F�N�g�̃��X�g
	std::list<std::unique_ptr<FBXobj3d>> objects;

	//�ǂ�list
	std::list<std::unique_ptr<Wall>> Walls;


	static  int wallNum;
	static  int enemyNum;



	//�n�`1���̃f�[�^
	struct WallData {
		XMFLOAT3 pos{};//���W
		XMFLOAT3 scale{};//�X�P�[��
		XMFLOAT3 rotation{};//���[�e�[�V����
		int modelname;//���f���̎w��
		XMFLOAT3 r;//�R���C�_�[�̔��a�w��
		int stage;//�X�e�[�W�̎w��
	}walldata;

	static XMFLOAT3 wallpos[];//���W
	static XMFLOAT3 wallscale;//�X�P�[��
	static XMFLOAT3 wallrotation;
	static int wallmodelname;//���f���̎w��
	static XMFLOAT3 wallr;//�R���C�_�[�̔��a�w��

	//std::list<std::unique_ptr<Wall>> Stage1Walls;
	//std::list<std::unique_ptr<Wall>> Stage2Walls;
	//std::list<std::unique_ptr<Wall>> Stage3Walls;
	//std::list<std::unique_ptr<Wall>> Stage4Walls;
	////�ǃR�}���h
	//std::stringstream wallDataS1;
	//std::stringstream wallDataS2;
	//std::stringstream wallDataS3;
	//std::stringstream wallDataS4;

	
	//2��
	FbxModel* modelobjgun = nullptr;
	Wall* tutogun = nullptr;
	Wall* stage2Object[3];

	FbxModel* modelBack = nullptr;
	FBXobj3d* backsphere = nullptr;

	
	//3d���f��(�G)

	//�G�̃��X�g
	std::list<std::unique_ptr<Enemy>> Enemys;

	//�G1�̕��̃f�[�^
	struct EnemyData {
		XMFLOAT3 pos{0,0,0};//���W
		XMFLOAT3 scale{0,0,0};//�X�P�[��
		int modelname=0;//���f���̎w��
		float r=0;//�R���C�_�[�̔��a�w��
		bool mod=false;//�G�̎�ނ̎w��
	}enemydata;
	
	static XMFLOAT3 enemypos;//���W
	static XMFLOAT3 enemyscale;//�X�P�[��
	static int enemymodelname;//���f���̎w��
	static float enemyr;//�R���C�_�[�̔��a�w��
	static bool emod;//�G�̎�ނ̎w��

	//std::list<std::unique_ptr<Enemy>> Stage1Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage2Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage3Enemy;
	//std::list<std::unique_ptr<Enemy>> Stage4Enemy;
	//
	//�G�R�}���h
	//std::stringstream enemyDataS2;
	//std::stringstream enemyDataS3;
	//std::stringstream enemyDataS4;

	

	//�`���[�g���A��
	//std::vector<int> tutonum;
	static int tutonum;
	int tutocount = 0;


	//���@�֘A
	Player* player = nullptr;
	PlayerCol* playercol = nullptr;

	float movect = 0;
	//�U��������
	bool attack = false;
	//�e�𓊂�����
	bool gunthrow = false;
	//�e�������Ă��邩
	bool have = false;
	//�c�e��
	int magazin = 0;


	///�J�����֘A
	//�ЂƂO�̃}�E�X�̍��W
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//�J���������ʒu
	XMFLOAT3 EyeInitialize = { 0,4,0 };
	//�f�o�b�O�p���Z�b�g�t���O
	int resetflag = 0;
	//�J�����̍X�V�����p
	int firstfrag = 0;
	//�v���C���[���ǂɂԂ����Ă��邩
	bool wallcol = false;


	//�V�[���֘A
	float timecount = 0;//���ԊǗ������ϐ�
	//���񂾂Ƃ��̃V�[��
	int diescene = 0;
	//�N���A�����V�[��
	int clearscene = 0;
	int tutoscene = 0;
	int goflag = 0;
	

};

