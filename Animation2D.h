#pragma once
#include <array>
#include <vector>
#include "global.h"
#include "GameObject.h"
class Animation2D : public GameObject
{
	int nowFrame_ = 0;// 現在のアニメーションフレーム
	int index_ = 0;
	float animTimer_;
	//std::array<int, 10> animTip_;//アニメーションのコマ番号
	int animTipNum_;
	float animInterval_;
	void Anim();
	Point frame;
public:
	
	Animation2D(float x, float y);
	
	void Update() override;
	void Draw() override;
};

