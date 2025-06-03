#pragma once
#include <array>
#include <vector>
#include "global.h"
#include "GameObject.h"
class Animation2D : public GameObject
{
	int hImage_;
	int nowFrame_ = 0;// ���݂̃A�j���[�V�����t���[��
	int index_ = 0;
	//�ŏ�3�т傤�A�m�F�o������1�b
	float animTimer_;
	std::array<int, 10> animTip_;//�A�j���[�V�����̃R�}�ԍ�
	float animInterval_ = 0.3f;
	//int imageSize_;
	void Anim();

public:
	
	Animation2D(float x, float y);
	Animation2D(int hImage, std::array<int, 4> animTip, float animInterval = 0.3f);
	void Update() override;
	void Draw() override;
};

