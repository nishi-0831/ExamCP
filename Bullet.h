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
	int isize_x, isize_y;//弾の表示サイズ、画像のサイズ
public:
	Bullet();
	Bullet(float x, float y);
	~Bullet();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
};

