#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "global.h"
#include <vector>
#include "Bullet.h"
#include <DxLib.h>
#include <cmath>
#include "ImGui/Imgui.h"
#include "Army.h"

namespace
{
	//stage.cppà»äOÇ≈ÇÕéQè∆Ç≈Ç´Ç»Ç≠Ç»ÇÈÇÊ
	//const float shootInterval = 0.5f;
	Army* army;
}

Stage::Stage()
	: GameObject() , player_(nullptr)
{
	AddGameObject(this);
	army = new Army();
	AddGameObject(army);
	player_ = new Player();
#if test
	enemy_ = std::vector<Enemy*>(ENEMY_NUM);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//MAX_ETYPEÇ≈äÑÇ¡ÇΩó]ÇËÇÕMAX_ETYPEñ¢ñûÇ…Ç»ÇÈÇÊ
		//enemy_[i] = new Enemy(i,(ETYPE)(i % MAX_ETYPE));
		//enemy_[i]->SetID(i);
		int row = i / ENEMY_COL_SIZE;
		int col = i % ENEMY_COL_SIZE;

		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS,KNIGHT,MID,ZAKO,ZAKO,ZAKO };
		ETYPE type;
		switch (row)
		{
		case 0:
			type = ETYPE::BOSS;
			break;
		case 1:
			type = ETYPE::KNIGHT;
			break;
		case 2:
			type = ETYPE::MID;
			break;
		default:
			type = ETYPE::ZAKO;
			break;
		}
		//enemy_[i] = new Enemy(i, type);
		enemy_[i] = new Enemy(i, enemyType[row]);
		enemy_[i]->SetID(i);
		enemy_[i]->SetPos(ARMY_MARGIN + col * ENEMY_ALIGN_X, 100 + row * ENEMY_ALIGN_Y);
	}
#endif
	hBackground_ = LoadGraph("Asset/bg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
#if test
	shootTimer_ += GetDeltaTime();
	if (shootTimer_ >= shootInterval)
	{
		Point point = enemy_[rand() % ENEMY_NUM]->GetPos();
		AddGameObject(new Bullet(point.x, point.y, Shooter::ENEMY));
		shootTimer_ -= shootInterval;
	}
#endif
	for(auto eneItr = enemy_.begin();eneItr != enemy_.end();)
	{
		if ((*eneItr) == nullptr)
		{
			++eneItr;
			continue;
		}
		//for (auto& a : player_->GetAllBullets())
		
		for(auto playerBulletItr = player_->GetAllBullets().begin(); playerBulletItr != player_->GetAllBullets().end(); ++playerBulletItr)

		{
			if ((*eneItr)->IsAlive() == false || !((*playerBulletItr)->IsFired()))
			{
				continue;
			}
			bool isInterSect = false;
			if (IntersectRect((*eneItr)->GetRect(), (*playerBulletItr)->GetRect()))
			{
				(*eneItr)->SetAlive(false);
				(*playerBulletItr)->SetFired(false);
			}
		}

		if ((*eneItr)->IsAlive())
		{
			++eneItr;
		}
		else
		{
			eneItr = enemy_.erase(eneItr);
		}
	}
#if test
 	for (auto& e : enemy_)
	{
		
		if (e == nullptr)
		{
			continue;
		}
		if (e->IsAlive() == false)
		{
			continue;
		}
		int MOVEMENT = 100;
		if (e->IsLeftEnd())
		{
			
			for (auto& ene : enemy_)
			{
				ene->ChangeMoveDirRight();
				//ene->MovePosY(MOVEMENT);	
			}
			return;
			
		}
		if (e->IsRightEnd())
		{
			for (auto& ene : enemy_ )
			{
				ene->ChangeMoveDirLeft();
				//ene->MovePosY(MOVEMENT);
				
			}
			return;
		}
	}
#endif
}

void Stage::Draw()
{	
}
