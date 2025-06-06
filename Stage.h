#pragma once
#include "GameObject.h"

#include <vector>

class Player; //‘O•ûéŒ¾
class Enemy;//‘O•ûéŒ¾

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

