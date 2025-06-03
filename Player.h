#pragma once
#include "GameObject.h"
#include "global.h"

class Bullet; //�O���錾

class Player : public GameObject
{
	int hImage_;//�v���C���[�̉摜�n���h��
	//float x_, y_;//�v���C���[�̍��W
	float speed_;//�v���C���[�̈ړ����x
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

