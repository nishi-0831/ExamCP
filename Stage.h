#pragma once
#include "GameObject.h"

#include <vector>

class Player; //�O���錾
class Enemy;//�O���錾

class Stage :
    public GameObject
{
private:
	Player* player_;
	std::vector<Enemy*> enemy_;
	int hBackground_;
	
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
};

