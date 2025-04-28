#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	int hImage_;//プレイヤーの画像ハンドル
	float x_, y_;//プレイヤーの座標
	float speed_;//プレイヤーの移動速度
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
};

