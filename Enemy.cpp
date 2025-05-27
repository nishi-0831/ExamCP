#include "Enemy.h"
#include "DxLib.h"
#include "global.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>

namespace
{
	
	const int ENEMY_MARGIN_X = ENEMY_IMAGE_WIDTH / 2;
	const int ENEMY_MARGIN_Y = ENEMY_IMAGE_HEIGHT / 2;
	
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;

	const float ENEMY_INIT_SPEED = 100.0f; //�����ړ����x
	const float ENEMY_INIT_X = 100.0f;//�G�̏���X���W
	const float ENEMY_INIT_Y = 100.0f;//�G�̏���Y���W

	const int LEFT_END = 0;
	const int RIGHT_END = WIN_WIDTH;

	enum MoveDir
	{
		left = -1,
		right = 1
	};
}
Enemy::Enemy(int id, ETYPE type)
	: GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), ID_(id),type_(type),dir_(1)
{
	std::string imagePath[MAX_ETYPE] =
	{
		"Assets\\tiny_ship10.png", //ZAKO
		"Assets\\tiny_ship18.png",//MID
		"Assets\\tiny_ship16.png",//KNIGHT
		"Assets\\tiny_ship9.png",//BOSS
	};

	hImage_ = LoadGraph(imagePath[type_].c_str());
	
	if (hImage_ == -1)
	{
		//�G���[��Ԃ��ăQ�[���I��
	}
	x_ = ENEMY_INIT_X;
	y_ = ENEMY_INIT_Y;
	speed_ = ENEMY_INIT_SPEED;
	AddGameObject(this);
	//id��type���w�肳��Ȃ������Ƃ��̏����������ɏ����˂�(�ȗ��B�����Ȃ�)
}
Enemy::Enemy()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0),dir_(1)
{

	hImage_ = LoadGraph("Assets\\tiny_ship10.png");
	if (hImage_ == -1)
	{
		//�G���[��Ԃ��ăQ�[���I��
	}
	x_ = ENEMY_INIT_X;
	y_ = ENEMY_INIT_Y;
	speed_ = ENEMY_INIT_SPEED;
}

Enemy::~Enemy()
{
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_);
	}
}

void Enemy::Update()
{
	float dt = GetDeltaTime();
	
	x_ += speed_ * dt * dir_;
	
	
	//��(��O�ɍs������`�`)
	
	//�N����̂��[�ɍs������S�����]����
	//���[��0�ԖځA�E�[�͖���
	//�I�u�W�F�N�g�v�[���̏ꍇ�A�z�����ёւ��Ė������L������Ƃ��A
	//��������@�\���L���ȓz��T������Ƃ�

	//�I�u�W�F�N�g�v�[���łȂ��폜�A�ǉ��̍ۂɔz��̃T�C�Y��ς���Ȃ�P��end�Ŗ����ł���
	
	//�[�ɍs��������Enemy�ȊO�����肷��B�S���܂Ƃ߂Ĕ��]������������B
	//���̍ہA��̓I�ȃf�[�^�\���ɃA�N�Z�X���Ă�ƌォ��ύX����ςȂ̂ŁAbool�֐��ŕԂ�

	//�R���N���X�Ƃ��������ق������̂�������Ȃ�
}

void Enemy::Draw()
{
	//Enemy�̍��W�̐^�񒆂ɉ摜�\��
	DrawExtendGraphF(x_ - ENEMY_MARGIN_X, y_ - ENEMY_MARGIN_Y, x_ + ENEMY_MARGIN_X, y_ + ENEMY_MARGIN_Y, hImage_, TRUE);
}

bool Enemy::IsLeftEnd()
{
	return (x_ < LEFT_END);
}

bool Enemy::IsRightEnd()
{
	//�E(��O)�ɂ�������`�`
	return (x_ + ENEMY_IMAGE_WIDTH > RIGHT_END);
}

void Enemy::ChangeMoveDirLeft()
{
	//x_ = WIN_WIDTH - ENEMY_IMAGE_WIDTH;
	//�G������̉��ԖڂŔz�u�����߂�K�v������
	dir_ = MoveDir::left;
}

void Enemy::ChangeMoveDirRight()
{
	//x_ = LEFT_END;
	dir_ = MoveDir::right;
}
