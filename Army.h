#pragma once
#include "GameObject.h"
#include "global.h"
#include <vector>
class Effect;
class Enemy;
enum ETYPE
{
	ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};
class Army :
	public GameObject
{
public:
	Army(int id, ETYPE type);
	Army(int id);
	Army();
	~Army();
	void Update() override;
	void Draw() override;
protected:
private:
	Effect* effect;

	std::vector<Enemy*> enemys_;
	int dir_;
	ETYPE type_;

};

