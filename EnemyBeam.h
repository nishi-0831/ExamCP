#pragma once
#include "GameObject.h"

//玉のサイズは13.0fと33.0f
class EnemyBeam :
	public GameObject
{
public:
	EnemyBeam();
	EnemyBeam(float x, float y);
	~EnemyBeam();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
	void SetFired(bool fired) { isFired_ = fired; }
	bool IsFired() const { return isFired_; }
	/*Rect GetRect() const {
		return { x_, y_, (float)imageSize_.x, (float)imageSize_.y };
	}*/
private:
	//int hImage_;
	//float x_, y_;
	float speed_;
	//Point imageSize_;
	//int isize_x, isize_y;//弾の表示サイズ、画像のサイズ
	bool isFired_;//発射されているかどうか

};

