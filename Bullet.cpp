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
	static int ENE_HImage;
	static bool flag = false;//“G‚Ì’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚ñ‚¾‚©‚Ç‚¤‚©
	const int BULLET_IMAGE_MARGIN = BULLET_IMAGE_WIDTH/2;
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
	//const char BULLET_IMAGE_PATH_CSTR[] = "Assets/laserBlue03.png";//’e‚Ì‰æ‘œ‚ÌƒpƒX
}



Bullet::Bullet()
	: GameObject(), speed_(0), isFired_{ false }
{
	if (!flag)
	{
		ENE_HImage = LoadGraph("Assets/ebeams.png");//“G‚Ì’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
		assert(!(ENE_HImage == -1));
		flag = true;
	}
	imageSize_ = { BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT };
 	//hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
	//assert(!(hImage_ == -1));
	speed_ = BULLET_INIT_SPEED;//ˆÚ“®‘¬“x
	isAlive_ = true;//’e‚Í¶‚«‚Ä‚¢‚é
	AddGameObject(this);
}

Bullet::Bullet(Shooter shooter) : Bullet()
{
	shooter_ = shooter;
	
	if (shooter == Shooter::ENEMY)
	{
		speed_ = 250.0f;
		isFired_ = true;
		//ENE_HImage = LoadGraph("Assets/ebeams.png");//“G‚Ì’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
		//hImage_ = LoadGraph("Assets/ebeams.png");
		hImage_ = ENE_HImage;
	}
	else if (shooter == Shooter::PLAYER)
	{
		speed_ = BULLET_INIT_SPEED;
		isFired_ = true;
		hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
		assert(!(hImage_ == -1));
	}
	else
	{
		assert(false && "Invalid shooter type");
	}
}



Bullet::Bullet(float x, float y, Shooter shooter)
	:Bullet(shooter)
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
		if (shooter_ == Shooter::PLAYER)
		{
			y_ -= (speed_ * dt);//’e‚ÌˆÚ“®
		}
		else if (shooter_ == Shooter::ENEMY)
		{
			//“G‚Ì’e‚Í‰º‚©‚çã‚ÉˆÚ“®
			y_ += (speed_ * dt);//’e‚ÌˆÚ“®
		}
		if (y_ < 0 - imageSize_.y || y_ > WIN_HEIGHT)
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

