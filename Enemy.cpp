#include "Enemy.h"
#include "DxLib.h"
#include "global.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>

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
	: GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), ID_(id),type_(type),dir_(1)
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
	AddGameObject(this);
	//idとtypeを指定されなかったときの処理をここに書かねば(省略。書かない)
}
Enemy::Enemy()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0),dir_(1)
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
	
	x_ += speed_ * dt * dir_;
	
	
	//左(場外に行ったら～～)
	
	//誰か一体が端に行ったら全員反転する
	//左端は0番目、右端は末尾
	//オブジェクトプールの場合、配列を並び替えて末尾を記憶するとか、
	//末尾から機能が有効な奴を探索するとか

	//オブジェクトプールでなく削除、追加の際に配列のサイズを変えるなら単にendで末尾でいい
	
	//端に行ったかはEnemy以外が判定する。全員まとめて反転させたいから。
	//その際、具体的なデータ構造にアクセスしてると後から変更が大変なので、bool関数で返す

	//軍隊クラスとかあったほういいのかもしれない
}

void Enemy::Draw()
{
	//Enemyの座標の真ん中に画像表示
	DrawExtendGraphF(x_ - ENEMY_MARGIN_X, y_ - ENEMY_MARGIN_Y, x_ + ENEMY_MARGIN_X, y_ + ENEMY_MARGIN_Y, hImage_, TRUE);
}

bool Enemy::IsLeftEnd()
{
	return (x_ < LEFT_END);
}

bool Enemy::IsRightEnd()
{
	//右(場外)にいったら～～
	return (x_ + ENEMY_IMAGE_WIDTH > RIGHT_END);
}

void Enemy::ChangeMoveDirLeft()
{
	//x_ = WIN_WIDTH - ENEMY_IMAGE_WIDTH;
	//敵が隊列の何番目で配置を決める必要がある
	dir_ = MoveDir::left;
}

void Enemy::ChangeMoveDirRight()
{
	//x_ = LEFT_END;
	dir_ = MoveDir::right;
}
