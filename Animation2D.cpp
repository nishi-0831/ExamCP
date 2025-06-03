#include "Animation2D.h"
#include <DxLib.h>

namespace
{
	int row = 3;
	int column = 3;
	Point frame = { 0,0 };
}
void Animation2D::Anim()
{
	animTimer_ += 0.016f;
	if (animTimer_ >= animInterval_)
	{
		//index_ = index_ % 4;
	//	nowFrame_ = animTip_[index_];
		frame.x = index_ / row;
		frame.y = index_ % row;
		animTimer_ -= animInterval_;
		index_++;
	}
}

Animation2D::Animation2D(float x, float y)
{
	hImage_ = LoadGraph("Assets/explosion.png");
	x_ = x;
	y_ = y;
	for (int i = 0;i < 10;i++)
	{
		animTip_[i] = i;//�A�j���[�V�����̃R�}�ԍ�
	}
	animInterval_ = 0.5f; //�A�j���[�V�����̊Ԋu
	animTimer_ = 0.0f; //�A�j���[�V�����^�C�}�[������
	imageSize_ = { 48, 48 }; //���̃T�C�Y
}

Animation2D::Animation2D(int hImage, std::array<int, 4> animTip, float animInterval)
	: hImage_(hImage), animInterval_(animInterval), animTimer_(0.0f)
{
	imageSize_ = { 64, 64 }; //���̃T�C�Y
}

void Animation2D::Update()
{
	Anim();
	if (index_ > animTip_.size())
	{
		//delete this;
		isAlive_ = false;
	}
}

void Animation2D::Draw()
{
	//�c48 ,��48
	//Rect rect{ pos_.x, pos_.y, pos_.x + image, pos_.y + CHA_SIZE };

	//3*3�̃A�j���`�b�v
	Rect rect = GetRect();
	//DrawRectExtendGraph(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, animTip_[nowFrame_] * imageSize_.x, imageSize_.y, rect.width, rect.height, hImage_, TRUE);
	if (frame.x >= animTip_.size() || frame.y >= animTip_.size())
	{
		Rect rect = GetRect();
	}
	DrawRectExtendGraph(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, frame.x * imageSize_.x,frame.y* imageSize_.y, rect.width, rect.height, hImage_, TRUE);
}

