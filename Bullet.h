#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{
private:
	int hImage_;
	float x_, y_;
	float speed_;
	bool isAlive_;
	int isize_x, isize_y;//�e�̕\���T�C�Y�A�摜�̃T�C�Y
public:
	Bullet();
	Bullet(float x, float y);
	~Bullet();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
};

