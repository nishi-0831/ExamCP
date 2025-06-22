#include "Player.h"
#include "DxLib.h"
#include "global.h"
#include "Input.h"
#include "Bullet.h"
#include <algorithm>


namespace
{
	const float PLAYER_INIT_SPEED = 250.0f; //初期移動速度
	

	const int PLAYER_BASE_MERGIN = 10;

	const float PLAYER_INIT_X = WIN_WIDTH / 2 - PLAYER_IMAGE_WIDTH/2; 
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MERGIN;

	const int BULLET_IMAGE_MARGIN = 17;
	const float BULLET_INTERVAL = 0.2f; //弾の間隔
	const int PLAYER_BULLET_NUM = 5;//プレイヤーが同時に発射できる弾の数
}
Player::Player()
//ハンドルは一般に正の整数
	:GameObject(),   speed_(0)
{
	imageSize_ = { PLAYER_IMAGE_WIDTH ,PLAYER_IMAGE_HEIGHT };
	//プレイヤーの画像を読み込む
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");
	if (hImage_ == -1)
	{
		//エラーを返してゲーム終了
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
	float dt = GetDeltaTime(); //フレーム間の時間差を取得
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
	//範囲外に行かないように
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


