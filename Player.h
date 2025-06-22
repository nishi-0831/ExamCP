#pragma once
#include "GameObject.h"
#include "global.h"
#include <memory>
class Bullet; //前方宣言

class Player : public GameObject
{
	float speed_;//プレイヤーの移動速度
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	void Shoot();
};

