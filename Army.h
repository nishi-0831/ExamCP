#pragma once
#include "GameObject.h"
#include "global.h"
#include <vector>
class Effect;
class Enemy;

class Army :
	public GameObject
{
	friend Enemy; //EnemyクラスからArmyのメンバにアクセスできるようにする
public:
	Army();
	~Army();
	void Update() override;
	void Draw() override;
	void IsOutOfScreen();
protected:
private:
	Effect* effect;
	float shootTimer_;
	Rect rect_;
	std::vector<Enemy*> enemys_;
	int dir_;
	ETYPE type_;
	float speed_;
};

