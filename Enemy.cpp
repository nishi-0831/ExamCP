#include "Enemy.h"
#include "DxLib.h"
#include "global.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; //画像の幅
	const int ENEMY_IMAGE_HEIGHT = 48; //画像の高さ
	
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;

	const float ENEMY_INIT_SPEED = 100.0f; //初期移動速度
	const float ENEMY_INIT_X = 100.0f;//敵の初期X座標
	const float ENEMY_INIT_Y = 100.0f;//敵の初期Y座標
}
Enemy::Enemy(int id, ETYPE type)
	: GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), isAlive_(true),ID_(id),type_(type)
{
	std::string imagePath[MAX_ETYPE] =
	{
		"Assets\\tiny_ship10.png", //ZAKO
		"Assets\\tiny_ship18.png",//MID
		"Assets\\tiny_ship16.png",//KNIGHT
		"Assets\\tiny_ship9.png",//BOSS
	};

	hImage_ = LoadGraph(imagePath[type_].c_str());
	
	if (hImage_ == -1)
	{
		//エラーを返してゲーム終了
	}
	x_ = ENEMY_INIT_X;
	y_ = ENEMY_INIT_Y;
	speed_ = ENEMY_INIT_SPEED;
	//idとtypeを指定されなかったときの処理をここに書かねば(省略。書かない)
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
	float dt = GetDeltaTime();
	
	//x_ += speed_ * dt;
	/*if (x_ + ENEMY_IMAGE_WIDTH > WIN_WIDTH || x_ < 0)
	{
		speed_ *= -1;
	}*/

	//右(場外)にいったら～～
	//if (x_ + ENEMY_IMAGE_WIDTH > WIN_WIDTH)
	//{
	//	x_ = WIN_WIDTH - ENEMY_IMAGE_WIDTH;
	//	//右に行ってるなら 右端において、左に進ませたい

	//	//これでspeed_は負になるはず
	//	speed_ = (std::min)(speed_, speed_ * -1);
	//}
	//else if()
}

void Enemy::Draw()
{
	//画面の左上に敵の画像を表示
	DrawExtendGraph(x_, y_, x_ + ENEMY_IMAGE_WIDTH, y_ + ENEMY_IMAGE_HEIGHT, hImage_, TRUE);
}
