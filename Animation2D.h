#pragma once
#include <array>
#include <vector>
#include "global.h"
#include "GameObject.h"
class Animation2D : public GameObject
{
	int hImage_;
	int nowFrame_ = 0;// 現在のアニメーションフレーム
	int index_ = 0;
	//最初3びょう、確認出来たら1秒
	float animTimer_;
	std::array<int, 10> animTip_;//アニメーションのコマ番号
	float animInterval_ = 0.3f;
	//int imageSize_;
	void Anim();

public:
	
	Animation2D(float x, float y);
	Animation2D(int hImage, std::array<int, 4> animTip, float animInterval = 0.3f);
	void Update() override;
	void Draw() override;
};

