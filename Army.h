#pragma once
#include "GameObject.h"
#include "global.h"
#include <vector>
#include <functional>
class Effect;
class Enemy;


class Army :
	public GameObject
{
	
public:
	Army();
	~Army();
	void Update() override;
	void Draw() override;
	void IsOutOfScreen();
	void Assault();
	void Notify(GameObject& target,Instruction instruction);
	//void NotifyDynamic(std::function<const PointF&()>& positionGetter,Instruction instruction);
	std::vector<Enemy*> enemys_;
	PointF GetReturnPos(int ID);
protected:
private:
	Effect* effect;
	float shootTimer_;
	Rect rect_;
	
	int dir_;
	ETYPE type_;
	float speed_;
};

