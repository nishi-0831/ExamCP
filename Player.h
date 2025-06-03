#pragma once
#include "GameObject.h"
#include "global.h"

class Bullet; //前方宣言

class Player : public GameObject
{
	int hImage_;//プレイヤーの画像ハンドル
	//float x_, y_;//プレイヤーの座標
	float speed_;//プレイヤーの移動速度
	std::vector<Bullet*> bullets_;
	//Point imageSize_;
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	void Shoot();
	Bullet* GetActiveBullet();
	Rect GetRect() const {
		return { x_, y_, imageSize_.x, imageSize_.y};
	}
	std::vector<Bullet*>& GetAllBullets()  {
		return bullets_;
	}
};

