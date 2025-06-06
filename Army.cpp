#include "Army.h"
#include "global.h"
#include "Enemy.h"

Army::Army()
    :GameObject()
{
    AddGameObject(this);

	enemy_ = std::vector<Enemy*>(ENEMY_NUM);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//MAX_ETYPE‚ÅŠ„‚Á‚½—]‚è‚ÍMAX_ETYPE–¢–ž‚É‚È‚é‚æ
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
}

Army::~Army()
{
}

void Army::Update()
{
}

void Army::Draw()
{
}

bool Army::InterSectEnemy(const Rect& bullet)
{
    for (auto ene : enemy_)
    {
        if (IntersectRect(ene->GetRect(), bullet))
        {
            ene->SetAlive(false);
            return true;
        }
    }
    return false;
}
