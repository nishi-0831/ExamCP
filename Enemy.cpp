#include "Enemy.h"
#include "DxLib.h"
#include "global.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>
#include "Animation2D.h"

namespace
{
	
	const int ENEMY_MARGIN_X = ENEMY_IMAGE_WIDTH / 2;
	const int ENEMY_MARGIN_Y = ENEMY_IMAGE_HEIGHT / 2;
	
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;

	const float ENEMY_INIT_SPEED = 100.0f; //初期移動速度
	const float ENEMY_INIT_X = 100.0f;//敵の初期X座標
	const float ENEMY_INIT_Y = 100.0f;//敵の初期Y座標

	const int LEFT_END = 0;
	const int RIGHT_END = WIN_WIDTH;

	enum MoveDir
	{
		left = -1,
		right = 1
	};
}

Enemy::Enemy(int id, ETYPE type)
	: GameObject(), speed_(0), ID_(id),type_(type),dir_(1)
{
	imageSize_ = { ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT };
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
	AddGameObject(this);
	//idとtypeを指定されなかったときの処理をここに書かねば(省略。書かない)
}
Enemy::Enemy()
	:GameObject()  ,speed_(0),dir_(1)
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
	this->effect = new Animation2D(x_, y_);
	SetAlive(false);
	AddGameObject(this->effect);
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_);
	}
}

void Enemy::Update()
{
	float dt = GetDeltaTime();
	
	x_ += speed_ * dt * dir_;
}

void Enemy::Draw()
{
	GameObject::Draw();
}

bool Enemy::IsLeftEnd()
{
	Rect rect = GetRect();
	return (rect.x < LEFT_END);
}

bool Enemy::IsRightEnd()
{
	//右(場外)にいったら～～
	Rect rect = GetRect();
	return (rect.width > RIGHT_END);
}

void Enemy::ChangeMoveDirLeft()
{
	dir_ = MoveDir::left;
}

void Enemy::ChangeMoveDirRight()
{
	//x_ = LEFT_END;
	dir_ = MoveDir::right;
}
