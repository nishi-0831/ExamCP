#include "Animation2D.h"
#include <DxLib.h>
#include "global.h"


namespace
{
	int row = 3;
	int column = 3;
	
}
void Effect::Anim()
{
	animTimer_ += GetDeltaTime();
	if (animTimer_ >= animInterval_)
	{
		frame.x = index_ % row;
		frame.y = index_ / row;
		animTimer_ -= animInterval_;
		index_++;
	}
}

Effect::Effect(float x, float y)
{
	hImage_ = LoadGraph("Assets/explosion.png");
	x_ = x;
	y_ = y;
	frame = { 0,0 };
	animTipNum_ = 10;
	float animTime = 1.0f;
	animInterval_ = animTime / animTipNum_; //�A�j���[�V�����̊Ԋu
	animTimer_ = 0.0f; //�A�j���[�V�����^�C�}�[������
	imageSize_ = { 48, 48 }; //���̃T�C�Y
}



void Effect::Update()
{
	Anim();
	if (index_ > animTipNum_)
	{
		isAlive_ = false;
	}
}

void Effect::Draw()
{
	//GameObject::Draw();
	//3*3�̃A�j���`�b�v
	Rect rect = GetRect();
	DrawRectExtendGraph(rect.x, rect.y, rect.width, rect.height, frame.x * imageSize_.x, frame.y * imageSize_.y, imageSize_.x, imageSize_.y, hImage_, TRUE);
	
}

