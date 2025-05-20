#include "global.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>

namespace
{
	const int BULLET_IMAGE_WIDTH = 13;//’e‚Ì‰æ‘œ‚Ì•
	const int BULLET_IMAGE_HEIGHT = 33;//’e‚Ì‰æ‘œ‚Ì‚‚³
	const float BULLET_INIT_SPEED = 200.0f;//’e‚Ì‰‘¬
	const std::string BULLET_IMAGE_PATH = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
	const int BULLET_IMAGE_MARGIN = 17;
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
	//const char BULLET_IMAGE_PATH_CSTR[] = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
}

Bullet::Bullet()
	: GameObject(),hImage_(-1),x_(0),y_(0), speed_(0),isize_x(BULLET_IMAGE_WIDTH),isize_y(BULLET_IMAGE_HEIGHT)
{
	isAlive_ = true;
 	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
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
	float dt = GetDeltaTime();
	y_ -=  (speed_ * dt);//’e‚ÌˆÚ“®
	if (y_ < 0 - isize_y)
	{
		isAlive_ = false;//‰æ–ÊŠO‚Éo‚½‚ç’e‚ğÁ‚·
	}
}

void Bullet::Draw()
{
	if (isAlive_)
	{
		int centerSizeX = isize_x / 2;
		int centerSizeY = isize_y / 2;
		DrawExtendGraph(x_ - centerSizeX, y_ - centerSizeY, x_ + isize_x - centerSizeX, y_ + isize_y - centerSizeY,
			hImage_, TRUE);//’e‚Ì•`‰æ
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
