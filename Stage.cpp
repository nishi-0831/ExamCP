#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "global.h"
#include <vector>
#include "Bullet.h"
namespace
{
	//stage.cppˆÈŠO‚Å‚ÍQÆ‚Å‚«‚È‚­‚È‚é‚æ
	
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;
	const int ENEMY_NUM = ENEMY_COL_SIZE * ENEMY_ROW_SIZE;
	bool IntersectRect(const Rect &a, const Rect &b)
	{
		//a‚Æb‚ª‚Ô‚Â‚©‚Á‚Ä‚¢‚é‚È‚çtrue
		if (a.y < b.y + b.height && a.y + a.height > b.y && a.x + a.width > b.x && a.x < b.x + b.width)
		{
			return true;
		}
		return false;
	}
}

Stage::Stage()
	: GameObject() , player_(nullptr)
{
	AddGameObject(this);
	player_ = new Player();
	enemy_ = std::vector<Enemy*>(ENEMY_NUM);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//MAX_ETYPE‚ÅŠ„‚Á‚½—]‚è‚ÍMAX_ETYPE–¢–‚É‚È‚é‚æ
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
		enemy_[i]->SetPos(100 + col * 50, 100 + row * 50);
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	//‹Ê‚Íplayer::bullets
	
	for (auto& e : enemy_)
	{
		for (auto& a : player_->GetAllBullets())
		{
			if (e->IsAlive() == false)
			{
				continue;
			}
			if (IntersectRect(e->GetRect(), a->GetRect()))
			{
				e->SetAlive(false);
				a->SetFired(false);
			}
		}
		
	}
	if ((*(enemy_.begin()))->IsLeftEnd())
	{	
	}
	else if ((*(enemy_.rbegin()))->IsLeftEnd())
	{
	}
	
}

void Stage::Draw()
{
	/*player_->Draw();
	for (auto& elm : enemy_)
	{
		elm->Draw();
	}*/
}
