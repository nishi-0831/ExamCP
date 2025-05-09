#include "Enemy.h"
#include "DxLib.h"

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; //�摜�̕�
	const int ENEMY_IMAGE_HEIGHT = 48; //�摜�̍���
	
	const float ENEMY_INIT_SPEED = 100.0f; //�����ړ����x
	const float ENEMY_INIT_X = 100.0f;//�G�̏���X���W
	const float ENEMY_INIT_Y = 100.0f;//�G�̏���Y���W
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
}

void Enemy::Draw()
{
	//��ʂ̍���ɓG�̉摜��\��
	DrawExtendGraph(x_, y_, x_ + ENEMY_IMAGE_WIDTH, y_ + ENEMY_IMAGE_HEIGHT, hImage_, TRUE);
}
