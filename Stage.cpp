#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "global.h"
#include <vector>
#include "Bullet.h"
#include <DxLib.h>
#include <cmath>
#include "ImGui/Imgui.h"

namespace
{
	//stage.cppà»äOÇ≈ÇÕéQè∆Ç≈Ç´Ç»Ç≠Ç»ÇÈÇÊ
	
	

	
}

Stage::Stage()
	: GameObject() , player_(nullptr)
{
	AddGameObject(this);
	player_ = new Player();
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
	hBackground_ = LoadGraph("Asset/bg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
	//ã ÇÕplayer::bullets
	/*for (int i = 0; i < enemy_.size(); i++)
	{
		if (enemy_[i] == nullptr) continue;

		std::vector<Bullet*> bullets = player_->GetAllBullets();
		for (int j = 0; j < bullets.size(); j++)
		{
			if ((enemy_[i]->IsAlive() == false) || (bullets[j]->IsFired() == false))
			{
				continue;
			}
			if (IntersectRect(enemy_[i]->GetRect(), bullets[j]->GetRect()))
			{
				enemy_.erase()
			}
		}
	}*/
	//for (auto& e : enemy_)
	for(auto eneItr = enemy_.begin();eneItr != enemy_.end();)
	{
		if ((*eneItr) == nullptr)
		{
			++eneItr;
			continue;
		}
		//for (auto& a : player_->GetAllBullets())
		for(auto playerItr = player_->GetAllBullets().begin(); playerItr != player_->GetAllBullets().end(); ++playerItr)

		{
			if ((*eneItr)->IsAlive() == false || !((*playerItr)->IsFired()))
			{
				
				continue;
			}
			bool isInterSect = false;
			if (IntersectRect((*eneItr)->GetRect(), (*playerItr)->GetRect()))
			{
				(*eneItr)->SetAlive(false);
				(*playerItr)->SetFired(false);
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
				ene->MovePosY(MOVEMENT);	
			}
			return;
			
		}
		if (e->IsRightEnd())
		{
			for (auto& ene : enemy_ )
			{
				ene->ChangeMoveDirLeft();
				ene->MovePosY(MOVEMENT);
				
			}
			return;
		}
	}
}

void Stage::Draw()
{
	ImGui::Begin("enemy");
	for (auto ene : enemy_)
	{
		Point pos = ene->GetPos();
		ImGui::Text("enemy[%d] : pos(%4.1f,%4.1f)", ene->GetID(),pos.x, pos.y);
	}
	ImGui::End();
	//
	/*player_->Draw();
	for (auto& elm : enemy_)
	{
		elm->Draw();
	}*/
	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA,)
	//DrawExtendGraph(0,)
}
