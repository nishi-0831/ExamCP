#include "Enemy.h"
#include "DxLib.h"

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; //画像の幅
	const int ENEMY_IMAGE_HEIGHT = 48; //画像の高さ
	
	const float ENEMY_INIT_SPEED = 100.0f; //初期移動速度
	const float ENEMY_INIT_X = 100.0f;//敵の初期X座標
	const float ENEMY_INIT_Y = 100.0f;//敵の初期Y座標
}
Enemy::Enemy()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), isAlive_(true)
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png");
	if (hImage_ == -1)
	{
		//エラーを返してゲーム終了
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
	//画面の左上に敵の画像を表示
	DrawExtendGraph(x_, y_, x_ + ENEMY_IMAGE_WIDTH, y_ + ENEMY_IMAGE_HEIGHT, hImage_, TRUE);
}
