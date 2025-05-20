#include "global.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>

namespace
{
	const int BULLET_IMAGE_WIDTH = 13;//�e�̉摜�̕�
	const int BULLET_IMAGE_HEIGHT = 33;//�e�̉摜�̍���
	const float BULLET_INIT_SPEED = 200.0f;//�e�̏���
	const std::string BULLET_IMAGE_PATH = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
	const int BULLET_IMAGE_MARGIN = 17;
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
	//const char BULLET_IMAGE_PATH_CSTR[] = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
}

Bullet::Bullet()
	: GameObject(),hImage_(-1),x_(0),y_(0), speed_(0),isize_x(BULLET_IMAGE_WIDTH),isize_y(BULLET_IMAGE_HEIGHT)
{
	isAlive_ = true;
 	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//�e�̉摜��ǂݍ���
	speed_ = BULLET_INIT_SPEED;//�ړ����x
	isAlive_ = true;//�e�͐����Ă���
	AddGameObject(this);
}



Bullet::Bullet(float x, float y)
	:Bullet()
{
	x_ = x;
	y_ = y;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	y_ -=  (speed_ * dt);//�e�̈ړ�
	if (y_ < 0 - isize_y)
	{
		isAlive_ = false;//��ʊO�ɏo����e������
	}
}

void Bullet::Draw()
{
	if (isAlive_)
	{
		int centerSizeX = isize_x / 2;
		int centerSizeY = isize_y / 2;
		DrawExtendGraph(x_ - centerSizeX, y_ - centerSizeY, x_ + isize_x - centerSizeX, y_ + isize_y - centerSizeY,
			hImage_, TRUE);//�e�̕`��
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
