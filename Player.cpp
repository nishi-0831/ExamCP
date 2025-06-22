#include "Player.h"
#include "DxLib.h"
#include "global.h"
#include "Input.h"
#include "Bullet.h"
#include <algorithm>


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
	:GameObject(),   speed_(0)
{
	imageSize_ = { PLAYER_IMAGE_WIDTH ,PLAYER_IMAGE_HEIGHT };
	//�v���C���[�̉摜��ǂݍ���
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");
	if (hImage_ == -1)
	{
		//�G���[��Ԃ��ăQ�[���I��
	}
	
	x_ = PLAYER_INIT_X;
	y_ = PLAYER_INIT_Y;
	speed_ = PLAYER_INIT_SPEED;
}

Player::~Player()
{

}

void Player::Update()
{
	float dt = GetDeltaTime(); //�t���[���Ԃ̎��ԍ����擾
	float dash = 0;
	if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
	{
		dash = speed_;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x_ -= (speed_+dash) * dt;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x_ += (speed_+dash) * dt;
	}
	//�͈͊O�ɍs���Ȃ��悤��
	Point center = GetImageCenter();
	x_ = std::clamp((int)x_, LEFT_END + center.x , RIGHT_END - center.x);
	static float bulletTimer = 0.0f;
	
	bulletTimer += dt;
	
	
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		if (bulletTimer > BULLET_INTERVAL)
		{
			bulletTimer = 0.0f;
			Shoot();
		}
	}
}

void Player::Draw()
{
	GameObject::Draw();
}


void Player::Shoot()
{
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->RegisterBullet(x_, y_, Shooter::PLAYER, PointF{ 0,-1.0f });
	
	/*bulletManager->Cleanup();
	auto bullet = CreateGameObject<Bullet>(x_, y_, Shooter::PLAYER, PointF{0,-1.0f});
	bullet->RegisterToManager();*/
}


