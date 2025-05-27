#include "Player.h"
#include "DxLib.h"
#include "global.h"
#include "Input.h"
#include "Bullet.h"

namespace
{
	const float PLAYER_INIT_SPEED = 250.0f; //�����ړ����x
	

	const int PLAYER_BASE_MERGIN = 10;

	const float PLAYER_INIT_X = WIN_WIDTH / 2 - PLAYER_IMAGE_WIDTH/2; 
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MERGIN;

	const int BULLET_IMAGE_MARGIN = 17;
	const float BULLET_INTERVAL = 0.2f; //�e�̊Ԋu
	const int PLAYER_BULLET_NUM = 5;//�v���C���[�������ɔ��˂ł���e�̐�
}
Player::Player()
//�n���h���͈�ʂɐ��̐���
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0)
{//�v���C���[�̉摜��ǂݍ���
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");
	if (hImage_ == -1)
	{
		//�G���[��Ԃ��ăQ�[���I��
	}
	
	x_ = PLAYER_INIT_X;
	y_ = PLAYER_INIT_Y;
	speed_ = PLAYER_INIT_SPEED;

	for (int i = 0;i < PLAYER_BULLET_NUM;i++)
	{
		bullets_.push_back(new Bullet());
	}
	AddGameObject(this);
}

Player::~Player()
{
}

void Player::Update()
{
	float dt = GetDeltaTime(); //�t���[���Ԃ̎��ԍ����擾
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x_ -= speed_ * dt;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x_ += speed_ * dt;
	}

	static float bulletTimer = 0.0f;
	if (bulletTimer > 0.0f)
	{
		bulletTimer -= dt;
	}
	
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		Shoot();
		/*if (bulletTimer <= 0.0f)
		{
			new Bullet(x_ + PLAYER_IMAGE_HEIGHT / 2, y_);
			bulletTimer = BULLET_INTERVAL;
		}*/
		
	}
}

void Player::Draw()
{
	//�v���C���[�̉摜��`��(�摜�̌��_�͍���)
	DrawExtendGraph(x_,y_, x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT, hImage_, TRUE);
}


void Player::Shoot()
{
	//for (auto& bullet : bullets_)
	//{
	//	if (!(bullet->IsFired()))
	//	{
	//		bullet->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);
	//		bullet->SetFired(true);
	//		break;//����˂����烋�[�v�𔲂���
	//	}
	//}

	Bullet* blt = GetActiveBullet();
	if (blt != nullptr)
	{
		blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);
		blt->SetFired(true);
	}
}

Bullet* Player::GetActiveBullet()
{
	for (auto& bullet : bullets_)
	{
		if (!bullet->IsFired())
		{
			return bullet;
		}
	}
	return nullptr;
}
