#pragma once
#include "GameObject.h"
#include "global.h"
//玉のサイズは13.0fと33.0f
class Bullet :
    public GameObject
{
public:
	Bullet();
	Bullet(Shooter shooter);
	Bullet(float x, float y, Shooter shooter);
	Bullet(float x, float y, Shooter shooter,PointF dir);
	~Bullet();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
	void SetFired(bool fired) { isFired_ = fired; }
	void SetDir(PointF dir);
	bool IsFired() const { return isFired_; }
	/*Rect GetRect() const {
		return { x_, y_, (float)imageSize_.x, (float)imageSize_.y };
	}*/
	Shooter GetShooter() { return shooter_; }
private:
	
	//int hImage_;
	//float x_, y_;
	Shooter shooter_;
	PointF dir_;
	float speed_;
	//Point imageSize_;
	//int isize_x, isize_y;//弾の表示サイズ、画像のサイズ
	bool isFired_;//発射されているかどうか

};

