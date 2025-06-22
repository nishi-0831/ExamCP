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
	static int ENE_HImage;
	static int PLA_HImage;
	static bool isEneImageLoaded = false;//�G�̒e�̉摜��ǂݍ��񂾂��ǂ���
	static bool isPlayerImageLoaded = false;
	const int BULLET_IMAGE_MARGIN = BULLET_IMAGE_WIDTH / 2;
	
}
// �ÓI�����o�̏�����
BulletManager* BulletManager::instance_ = nullptr;

Bullet::Bullet()
	: GameObject(),  dir_({ 0.0f, -1.0f }), speed_(300.0f), isFired_(false)
{
	
	imageSize_ = { BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT };
	imageSize_ = { 13, 33 };
	if (hImage_ == -1) {
		// �G���[����
	}
	
}

Bullet::Bullet(Shooter shooter)
	: Bullet()
{
	shooter_ = shooter;
	if (!isEneImageLoaded)
	{
		ENE_HImage = LoadGraph("Assets/ebeams.png");//�G�̒e�̉摜��ǂݍ���
		assert(!(ENE_HImage == -1));
		isEneImageLoaded = true;
	}
	if (!isPlayerImageLoaded)
	{
		PLA_HImage = LoadGraph(BULLET_IMAGE_PATH.c_str());//�e�̉摜��ǂݍ���
		assert(!(ENE_HImage == -1));
		isPlayerImageLoaded = true;
	}
	if (shooter_ == Shooter::ENEMY)
	{
		isFired_ = true;
		hImage_ = ENE_HImage;
	}
	if (shooter_ == Shooter::PLAYER)
	{
		
		hImage_ = PLA_HImage;
		assert(!(hImage_ == -1));
	}
}

Bullet::Bullet(float x, float y, Shooter shooter)
	: Bullet(shooter)
{
	x_ = x;
	y_ = y;
	isFired_ = true;

	
}

Bullet::Bullet(float x, float y, Shooter shooter, PointF dir)
	: Bullet(x, y, shooter)
{
	dir_ = dir;
	
}

Bullet::~Bullet()
{
	if (hImage_ != -1) {
		
	}
}
// Reset �̎���
void Bullet::Reset()
{
	dir_ = { 0.0f, -1.0f };
	speed_ = 300.0f;
	isFired_ = false;
	imageSize_ = { 13, 33 };
	SetActive(true);  // GameObject �̏�Ԃ����Z�b�g
}

void Bullet::Reset(Shooter shooter)
{
	Reset();  // ��{�I�ȃ��Z�b�g���s��
	shooter_ = shooter;

	if (shooter == Shooter::ENEMY)
	{
		isFired_ = true;
		hImage_ = ENE_HImage;
	}
	else if (shooter == Shooter::PLAYER)
	{
		hImage_ = PLA_HImage;
	}
}

void Bullet::Reset(float x, float y, Shooter shooter)
{
	Reset(shooter);  // �V���[�^�[�̃��Z�b�g���s��
	x_ = x;
	y_ = y;
	isFired_ = true;
}

void Bullet::Reset(float x, float y, Shooter shooter, PointF dir)
{
	Reset(x, y, shooter);  // �ʒu�ƃV���[�^�[�̃��Z�b�g���s��
	dir_ = dir;
}
void Bullet::Update()
{
	if (!isFired_) {
		return;
	}

	float dt = GetDeltaTime();
	x_ += dir_.x * speed_ * dt;
	y_ += dir_.y * speed_ * dt;

	// ��ʊO�ɏo�����A�N�e�B�u��
	if (x_ < 0 || x_ > WIN_WIDTH || y_ < 0 || y_ > WIN_HEIGHT) {
		//SetActive(false);
		isFired_ = false;
	}
}

void Bullet::Draw()
{
	if (isFired_) {
		GameObject::Draw();
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}

void Bullet::SetDir(PointF dir)
{
	dir_ = dir;
}

#if 0
#include "global.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>
#include <assert.h>
#include "BulletManager.h"
#include <memory>
namespace
{
	const int BULLET_IMAGE_WIDTH = 13;//�e�̉摜�̕�
	const int BULLET_IMAGE_HEIGHT = 33;//�e�̉摜�̍���
	const float BULLET_INIT_SPEED = 200.0f;//�e�̏���
	const std::string BULLET_IMAGE_PATH = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
	static int ENE_HImage;
	static bool flag = false;//�G�̒e�̉摜��ǂݍ��񂾂��ǂ���
	const int BULLET_IMAGE_MARGIN = BULLET_IMAGE_WIDTH/2;
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
	//const char BULLET_IMAGE_PATH_CSTR[] = "Assets/laserBlue03.png";//�e�̉摜�̃p�X
}



Bullet::Bullet()
	: GameObject(), speed_(0), isFired_{ false }
{
	if (!flag)
	{
		ENE_HImage = LoadGraph("Assets/ebeams.png");//�G�̒e�̉摜��ǂݍ���
		assert(!(ENE_HImage == -1));
		flag = true;
	}
	imageSize_ = { BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT };
 	//hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//�e�̉摜��ǂݍ���
	//assert(!(hImage_ == -1));
	speed_ = BULLET_INIT_SPEED;//�ړ����x
	isAlive_ = true;//�e�͐����Ă���
	BulletManager::GetInstance()->RegisterBullet(std::dynamic_pointer_cast<Bullet>(shared_from_this()));
}

Bullet::Bullet(Shooter shooter) : Bullet()
{
	shooter_ = shooter;
	
	if (shooter == Shooter::ENEMY)
	{
		speed_ = 250.0f;
		isFired_ = true;
		dir_.x = 0.0f;
		dir_.y = 1.0f;
		hImage_ = ENE_HImage;
	}
	else if (shooter == Shooter::PLAYER)
	{
		speed_ = BULLET_INIT_SPEED;
		isFired_ = true;
		hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());//�e�̉摜��ǂݍ���
		dir_.x = 0.0f;
		dir_.y = -1.0f;
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

Bullet::Bullet(float x, float y, Shooter shooter, PointF dir)
	:Bullet(x,y,shooter)
{
	dir_ = dir;

}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (isFired_)
	{
		float dt = GetDeltaTime();
#if 0
		if (shooter_ == Shooter::PLAYER)
		{
			y_ += (speed_ * dt * dir_.y);//�e�̈ړ�
		}
		else if (shooter_ == Shooter::ENEMY)
		{
			//�G�̒e�͉������Ɉړ�
			y_ += (speed_ * dt);//�e�̈ړ�
		}
#endif
		x_ += (speed_ * dt * dir_.x);
		y_ += (speed_ * dt * dir_.y);
		if (y_ < 0 - imageSize_.y || y_ > WIN_HEIGHT)
		{
			isFired_ = false;
		}
		if (x_ < 0 - imageSize_.x || x_ > WIN_WIDTH)
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

void Bullet::SetDir(PointF dir)
{
	dir_ = dir;
}

#endif

void BulletManager::Cleanup()
{
	
		bullets_.erase(
			std::remove_if(bullets_.begin(), bullets_.end(),
				[](const auto& bullet) {
					return bullet.expired() || !(bullet.lock()->IsAlive());
				}
			),
			bullets_.end()
		);
	
}
