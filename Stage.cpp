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
	//stage.cppˆÈŠO‚Å‚ÍŽQÆ‚Å‚«‚È‚­‚È‚é‚æ
	
	

	
}

Stage::Stage()
	: GameObject() , player_(nullptr)
{
	AddGameObject(this);
	player_ = new Player();
	
	hBackground_ = LoadGraph("Asset/bg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
	
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
}
