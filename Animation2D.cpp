#include "Animation2D.h"
#include <DxLib.h>
#include "global.h"
#include <string>
#include <vector>

namespace
{
	enum State
	{
		ONE_SHOT,
		LOOP
	};
	State state = State::ONE_SHOT;
	int row = 3;
	int column = 3;
	const std::string EIMAGE_PATH = "Assets/explosion.png";
	const int MAX_FRAME = 9;
	const int DIV_NUM = 3;
	const int IMAGE_SIZE = 48;
	std::vector<int> hImages;
}
void Effect::Anim()
{
	animTimer_ += GetDeltaTime();
#if 0
	if (animTimer_ >= animInterval_)
	{
		frame.x = index_ % row;
		frame.y = index_ / row;
		animTimer_ -= animInterval_;
		index_++;
	}
#endif
	if (animTimer_ >= animInterval_)
	{
		animTimer_ -= animInterval_;
		index_++;
		if (state == State::LOOP)
		{
			index_ = index_ % MAX_FRAME;
		}
		
	}
}
//����	FileName�@�@�@ : �����ǂݍ��݂���摜�t�@�C��������̃|�C���^
//AllNum�@�@�@�@ : �摜�̕�������
//XNum, YNum�@�@ : �摜�̉������ɑ΂��镪�����Əc�ɑ΂��镪����
//SizeX, SizeY�@ : �������ꂽ�摜��̑傫��
//HandleBuf�@�@ : �����ǂݍ��݂��ē����O���t�B�b�N�n���h����
//�ۑ�����int�^�̔z��ւ̃|�C���^
Effect::Effect(float x, float y)
{
	hImage_ = LoadGraph("Assets/explosion.png");
	hImages.resize(MAX_FRAME);
	LoadDivGraph(EIMAGE_PATH.c_str(),
		MAX_FRAME, column, row, IMAGE_SIZE, IMAGE_SIZE, hImages.data());
	x_ = x;
	y_ = y;
	frame = { 0,0 };
	animTipNum_ = 10;
	float animTime = 1.0f;
	animInterval_ = animTime / animTipNum_; //�A�j���[�V�����̊Ԋu
	animTimer_ = 0.0f; //�A�j���[�V�����^�C�}�[������
	imageSize_ = { IMAGE_SIZE, IMAGE_SIZE }; //���̃T�C�Y
}



void Effect::Update()
{
	Anim();
	if (index_ >= MAX_FRAME)
	{
		isAlive_ = false;
	}
}

void Effect::Draw()
{
	//GameObject::Draw();
	//3*3�̃A�j���`�b�v
	if (index_ >= MAX_FRAME) return;

	Rect rect = GetRect();
	//DrawRectExtendGraph(rect.x, rect.y, rect.width, rect.height, frame.x * imageSize_.x, frame.y * imageSize_.y, imageSize_.x, imageSize_.y, hImage_, TRUE);
	
	int frameX = index_ % column;
	int frameY = index_ / column;
	
	DrawGraph(rect.x, rect.y, hImages[index_],TRUE);
}

