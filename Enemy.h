#pragma once
#include "GameObject.h"
class Enemy :
    public GameObject
{
	int hImage_;//“G‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	float x_, y_;//“G‚ÌÀ•W
	float speed_;//“G‚ÌˆÚ“®‘¬“x
	bool isAlive_;//“G‚Ì¶€
public:
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x, y_ = y; }
};

