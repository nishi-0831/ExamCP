#pragma once
#include "GameObject.h"
#include "global.h"
#include <memory>
class Bullet; //�O���錾

class Player : public GameObject
{
	float speed_;//�v���C���[�̈ړ����x
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	void Shoot();
};

