#include "Player.h"
#include "DxLib.h"
#include "global.h"
#include "Input.h"
namespace
{
	const float PLAYER_INIT_SPEED = 5.0f; //初期移動速度
	const int PLAYER_IMAGE_WIDTH = 64; //画像の幅
	const int PLAYER_IMAGE_HEIGHT = 64; //画像の高さ

	const int PLAYER_BASE_MERGIN = 10;

	const float PLAYER_INIT_X = WIN_WIDTH / 2 - PLAYER_IMAGE_WIDTH/2; 
	
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MERGIN;
}
Player::Player()
//ハンドルは一般に正の整数
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0)
{//プレイヤーの画像を読み込む
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");
	if (hImage_ == -1)
	{
		//エラーを返してゲーム終了
	}
	//マジックナンバー!!!
	x_ = PLAYER_INIT_X;
	y_ = PLAYER_INIT_Y;
	speed_ = PLAYER_INIT_SPEED;
}

Player::~Player()
{
}

void Player::Update()
{
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x_ -= speed_ * GetDeltaTime();
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x_ += speed_ * GetDeltaTime();
	}
}

void Player::Draw()
{
	DrawExtendGraph(x_,y_, x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT, hImage_, TRUE);
}
