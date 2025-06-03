#pragma once
#include "GameObject.h"

//�ʂ̃T�C�Y��13.0f��33.0f
class Bullet :
    public GameObject
{
public:
	Bullet();
	Bullet(float x, float y);
	~Bullet();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
	void SetFired(bool fired) { isFired_ = fired; }
	bool IsFired() const { return isFired_; }
	Rect GetRect() const {
		return { x_, y_, (float)imageSize_.x, (float)imageSize_.y };
	}
private:
	int hImage_;
	float x_, y_;
	float speed_;
	Point imageSize_;
	//int isize_x, isize_y;//�e�̕\���T�C�Y�A�摜�̃T�C�Y
	bool isFired_;//���˂���Ă��邩�ǂ���

};

