#pragma once
#include "GameObject.h"
#include "global.h"
#include <memory>
#include <vector>

class Player; //‘O•ûéŒ¾
class Enemy;//‘O•ûéŒ¾

class Stage :
    public GameObject
{
private:
	//Player* player_;
	GameObjectWeakPtr player_;
	//std::vector<Enemy*> enemy_;
	std::vector<std::weak_ptr<Enemy>> enemy_;
	int hBackground_;
	//float shootTimer_;

public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	void GameOver();
	PointF GetPlayerPos();
};

