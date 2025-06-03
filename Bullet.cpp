#include "global.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>
#include <assert.h>
namespace
{
	const int BULLET_IMAGE_WIDTH = 13;//’e‚Ì‰æ‘œ‚Ì•
	const int BULLET_IMAGE_HEIGHT = 33;//’e‚Ì‰æ‘œ‚Ì‚‚³
	const float BULLET_INIT_SPEED = 200.0f;//’e‚Ì‰‘¬
	const std::string BULLET_IMAGE_PATH = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
	const int BULLET_IMAGE_MARGIN = BULLET_IMAGE_WIDTH/2;
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
	//const char BULLET_IMAGE_PATH_CSTR[] = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
}

Bullet::Bullet()
	: GameObject(), speed_(0), isFired_{ false }
{
	imageSize_ = { BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT };
 	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
	assert(!(hImage_ == -1));
	speed_ = BULLET_INIT_SPEED;//ˆÚ“®‘¬“x
	isAlive_ = true;//’e‚Í¶‚«‚Ä‚¢‚é
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
		y_ -= (speed_ * dt);//’e‚ÌˆÚ“®
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
		//	hImage_, TRUE);//’e‚Ì•`‰æ
		//Rect rect = GetRect();
		//Bullet‚ÌÀ•W‚Ì^‚ñ’†‚É‰æ‘œ•\¦
		//DrawExtendGraphF(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, hImage_, TRUE);
		//DrawBox(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, GetColor(255, 0, 0), FALSE);
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
