#include "Enemy.h"
#include "DxLib.h"
#include "global.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; //�摜�̕�
	const int ENEMY_IMAGE_HEIGHT = 48; //�摜�̍���
	
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;

	const float ENEMY_INIT_SPEED = 100.0f; //�����ړ����x
	const float ENEMY_INIT_X = 100.0f;//�G�̏���X���W
	const float ENEMY_INIT_Y = 100.0f;//�G�̏���Y���W
}
Enemy::Enemy(int id, ETYPE type)
	: GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), isAlive_(true),ID_(id),type_(type)
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
	//id��type���w�肳��Ȃ������Ƃ��̏����������ɏ����˂�(�ȗ��B�����Ȃ�)
}
Enemy::Enemy()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), isAlive_(true)
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
	
	//x_ += speed_ * dt;
	/*if (x_ + ENEMY_IMAGE_WIDTH > WIN_WIDTH || x_ < 0)
	{
		speed_ *= -1;
	}*/

	//�E(��O)�ɂ�������`�`
	//if (x_ + ENEMY_IMAGE_WIDTH > WIN_WIDTH)
	//{
	//	x_ = WIN_WIDTH - ENEMY_IMAGE_WIDTH;
	//	//�E�ɍs���Ă�Ȃ� �E�[�ɂ����āA���ɐi�܂�����

	//	//�����speed_�͕��ɂȂ�͂�
	//	speed_ = (std::min)(speed_, speed_ * -1);
	//}
	//else if()
}

void Enemy::Draw()
{
	//��ʂ̍���ɓG�̉摜��\��
	DrawExtendGraph(x_, y_, x_ + ENEMY_IMAGE_WIDTH, y_ + ENEMY_IMAGE_HEIGHT, hImage_, TRUE);
}
