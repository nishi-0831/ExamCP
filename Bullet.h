#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{
private:
	int hImage_;
	float x_, y_;
	float speed_;
	
	int isize_x, isize_y;//弾の表示サイズ、画像のサイズ
	bool isFired_;//発射されているかどうか
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
		return { x_, y_, (float)isize_x, (float)isize_y };
	}
};

