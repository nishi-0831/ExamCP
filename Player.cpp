#include "Player.h"
#include "DxLib.h"
#include "global.h"
#include "Input.h"
namespace
{
	const float PLAYER_INIT_SPEED = 250.0f; //�����ړ����x
	const int PLAYER_IMAGE_WIDTH = 64; //�摜�̕�
	const int PLAYER_IMAGE_HEIGHT = 64; //�摜�̍���

	const int PLAYER_BASE_MERGIN = 10;

	const float PLAYER_INIT_X = WIN_WIDTH / 2 - PLAYER_IMAGE_WIDTH/2; 
	
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MERGIN;
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
	//�}�W�b�N�i���o�[!!!
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
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x_ -= speed_ * dt;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x_ += speed_ * dt;
	}
}

void Player::Draw()
{
	//�v���C���[�̉摜��`��(�摜�̌��_�͍���)
	DrawExtendGraph(x_,y_, x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT, hImage_, TRUE);
}
