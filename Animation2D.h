#pragma once
#include <array>
#include <vector>
#include "global.h"
#include "GameObject.h"
class Effect : public GameObject
{
	int nowFrame_ = 0;// ���݂̃A�j���[�V�����t���[��
	int index_ = 0;
	float animTimer_;
	//std::array<int, 10> animTip_;//�A�j���[�V�����̃R�}�ԍ�
	int animTipNum_;
	float animInterval_;
	void Anim();
	Point frame;
public:
	
	Effect(float x, float y);
	
	void Update() override;
	void Draw() override;
};

