#include "global.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>
#include <assert.h>
namespace
{
	const int BULLET_IMAGE_WIDTH = 13;//�e�̉摜�̕�
	const int BULLET_IMAGE_HEIGHT = 33;//�e�̉摜�̍���
	const float BULLET_INIT_SPEED = 200.0f;//�e�̏���
	const std::string BULLET_IMAGE_PATH = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
	const int BULLET_IMAGE_MARGIN = BULLET_IMAGE_WIDTH/2;
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
	//const char BULLET_IMAGE_PATH_CSTR[] = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
}

Bullet::Bullet()
	: GameObject(), speed_(0), isFired_{ false }
{
	imageSize_ = { BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT };
 	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//�e�̉摜��ǂݍ���
	assert(!(hImage_ == -1));
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
	if (isFired_)
	{
		float dt = GetDeltaTime();
		y_ -= (speed_ * dt);//�e�̈ړ�
		if (y_ < 0 - imageSize_.y)
		{
			isFired_ = false;
		}
	}
}

void Bullet::Draw()
{
	if (isFired_)
	{
		GameObject::Draw();
		//int centerSizeX = imageSize_.x / 2;
		//int centerSizeY = imageSize_.y / 2;
		//DrawExtendGraphF(x_ - centerSizeX, y_ - centerSizeY, x_ + imageSize_.x - centerSizeX, y_ + imageSize_.y - centerSizeY,
		//	hImage_, TRUE);//�e�̕`��
		//Rect rect = GetRect();
		//Bullet�̍��W�̐^�񒆂ɉ摜�\��
		//DrawExtendGraphF(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, hImage_, TRUE);
		//DrawBox(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, GetColor(255, 0, 0), FALSE);
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
