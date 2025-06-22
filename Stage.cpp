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
#include <memory>
namespace
{
	//stage.cpp�ȊO�ł͎Q�Ƃł��Ȃ��Ȃ��
	//const float shootInterval = 0.5f;
	std::weak_ptr<Army> army;
}

Stage::Stage()
	: GameObject()
{
	//shared_from_this()->CreateGameObject<Stage>();
	army = CreateGameObject<Army>();
	if (auto ptr = army.lock())
	{
		enemy_ = ptr->enemys_;
	}
	
	player_ = CreateGameObject<Player>();
#if test
	enemy_ = std::vector<Enemy*>(ENEMY_NUM);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//MAX_ETYPE�Ŋ������]���MAX_ETYPE�����ɂȂ��
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
	BulletManager* bulletManager = BulletManager::GetInstance();

	bulletManager->CleanUp();

	for (const auto& bulletWeak : *bulletManager)
	{
		if (auto bullet = bulletWeak.lock())
		{
			if (!bullet->IsFired())
			{
				continue;
			}
			if (bullet->GetShooter() == Shooter::ENEMY)
			{
				if (auto playerPtr = player_.lock())
				{
					if (IntersectRect(bullet->GetRect(), playerPtr->GetRect()))
					{
						//�v���C���[�����j�����
						gameState = GameState::GAMEOVER;
					}
				}

			}
			else
			{
				for (const auto& enemyWeak : enemy_)
				{
					if (auto enemy = enemyWeak.lock())
					{
						if (IntersectRect(bullet->GetRect(), enemy->GetRect()))
						{
							enemy->SetAlive(false);
							bullet->SetFired(false);
						}
					}
				}
			}
		}
	}
#endif

	auto* bulletManager = BulletManager::GetInstance();

	// �����Ȓe�̍폜
	bulletManager->Cleanup();

	// �����蔻��`�F�b�N
	for (const auto& bulletWeak : bulletManager->GetAllBullets()) {
		if (auto bullet = bulletWeak.lock()) {
			if (bullet->IsAlive() && bullet->IsFired()) {
				if (bullet->GetShooter() == Shooter::ENEMY) {
					// �v���C���[�Ƃ̓����蔻��
					if (auto player = player_.lock()) {
						if (IntersectRect(bullet->GetRect(), player->GetRect())) {
							// �Փˏ���
							bullet->SetActive(false);
							// �v���C���[�ւ̃_���[�W����
 							gameState = GameState::GAMEOVER;
						}
					}
				}
				else {
					// �G�Ƃ̓����蔻��
					for (const auto& enemyWeak : enemy_) {
						if (auto enemy = enemyWeak.lock()) {
							if (enemy->IsAlive() && IntersectRect(bullet->GetRect(), enemy->GetRect())) {
								// �Փˏ���
								bullet->SetActive(false);
								enemy->SetActive(false);
								// �X�R�A���Z�Ȃ�
								break;
							}
						}
					}
				}
			}
		}
	}
#if 0
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
#endif
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

void Stage::GameOver()
{

}

PointF Stage::GetPlayerPos()
{
	return PointF();
}
