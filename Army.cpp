#define _USE_MATH_DEFINES
#include "Army.h"
#include "Enemy.h"
#include "global.h"
#include <DxLib.h>
#include "Time.h"
#include "Bullet.h"
#include  <math.h>
#include "ImGui/imgui.h"
#include "lerp.h"
#include "Player.h"
#include <algorithm>
namespace
{
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;
	const int ENEMY_NUM = 20;
	//const int ENEMY_NUM = ENEMY_COL_SIZE * ENEMY_ROW_SIZE;

	const int ENEMY_ALIGN_X = 50;
	const int ENEMY_ALIGN_Y = 50;

	//矩形領域
	const int ARMY_RECT_X = (WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COL_SIZE)) / 2;
	const int ARMY_RECT_WIDTH = WIN_WIDTH - ARMY_RECT_X - ARMY_RECT_X;
	const int ARMY_RECT_Y = (WIN_HEIGHT - (ENEMY_ALIGN_Y * ENEMY_ROW_SIZE)) / 2 -150;
	const int ARMY_RECT_HEIGHT = WIN_HEIGHT - ARMY_RECT_Y - ARMY_RECT_Y;

	const int ENEMY_MARGIN_X = ENEMY_IMAGE_WIDTH / 2;
	const int ENEMY_MARGIN_Y = ENEMY_IMAGE_HEIGHT / 2;

	const float ENEMY_INIT_SPEED = 100.0f; //初期移動速度
	const float ENEMY_INIT_X = 100.0f;//敵の初期X座標
	const float ENEMY_INIT_Y = 100.0f;//敵の初期Y座標

	////
	const int ARMY_INIT_X = 100.0f;
	const int ARMY_INIT_Y = 100.0f;

	const float shootInterval = 2.0f;

	int rightEnd = ENEMY_ROW_SIZE;

	static int radius = 10;
	static int tx = 180;
	static int ty = 180;
	static int degree = 0;

	std::vector<Point> table;
	//lerp lerpPos;
	int x = WIN_WIDTH / 3;
	int y = WIN_HEIGHT / 3;

	int idx = 0;
	
	/*const float attackInterval = 6.0f;
	float attackTimer = 0.0f;*/
	;
	
	const float assaultInterval = 3.0f;
	float assaultTimer = 0.0f;
	Player* player;
}

Army::Army()
{
	for (int i = 0; i < 9; i++)
	{
		int col = i % 3 + 1;
		int row = i / 3 + 1;
		Point pos{ (x * col) / 2,(y * row) / 2 };
		table.push_back(pos);
	}
	rect_.x = ARMY_RECT_X;
	rect_.y = ARMY_RECT_Y;
	rect_.width = rect_.x + ARMY_RECT_WIDTH;
	rect_.height = rect_.y + ARMY_RECT_HEIGHT;
	dir_ = 1;
	speed_ = 50.0f;
	shootTimer_ = 0.0f;
	//enemys_ = std::vector<Enemy*>(ENEMY_NUM);
	//enemys_.resize(ENEMY_NUM);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//MAX_ETYPEで割った余りはMAX_ETYPE未満になるよ
		//enemys_[i] = new Enemy(i,(ETYPE)(i % MAX_ETYPE));
		//enemys_[i]->SetID(i);
		int row = i / ENEMY_COL_SIZE;
		int col = i % ENEMY_COL_SIZE;

		ETYPE enemyType[ENEMY_ROW_SIZE] = { ETYPE::BOSS,ETYPE::KNIGHT,ETYPE::MID,ETYPE::ZAKO,ETYPE::ZAKO,ETYPE::ZAKO };
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
		
		auto enemy = CreateGameObject<Enemy>(i, enemyType[row], rect_.x + col * ENEMY_ALIGN_X, rect_.y + row * ENEMY_ALIGN_Y);
		enemys_.push_back(enemy);
	}
}


Army::~Army()
{
}

void Army::Update()
{
	CheckEnemys();
	Shoot();
	
	IsOutOfScreen();
	//移動
	float dt = Time::DeltaTime();
	rect_.x += dt * speed_ * dir_;
	rect_.width = rect_.x + ARMY_RECT_WIDTH;
	for (auto ene : enemys_)
	{
		if(auto ptr = ene.lock())
		{
			if (ptr->nowInstruction_ == Instruction::STANDBY)
			{
				int row = ptr->GetID() / ENEMY_COL_SIZE;
				int col = ptr->GetID() % ENEMY_COL_SIZE;
				ptr->SetPos(rect_.x + col * ENEMY_ALIGN_X, rect_.y + row * ENEMY_ALIGN_Y);
			}
		}
	}

	//突撃
	assaultTimer += GetDeltaTime();
	if (assaultTimer >= assaultInterval)
	{
		Assault();
		assaultTimer = 0.0f;
	}
}
void Army::Shoot()
{
	//射撃
	shootTimer_ += GetDeltaTime();
	if (shootTimer_ >= shootInterval)
	{
		int idx = rand() % enemys_.size();

		if (auto ptr = enemys_[idx].lock())
		{
			Point point = ptr->GetPos();
			BulletManager* bulletManager = BulletManager::GetInstance();
			bulletManager->RegisterBullet(point.x, point.y, Shooter::ENEMY, PointF{ 0,1.0f });
			
			shootTimer_ -= shootInterval;
		}
		else
		{
		}
	}
}
void Army::Draw()
{

}

void Army::IsOutOfScreen()
{
	for (auto& e : enemys_)
	{
		if (auto ptr = e.lock())
		{
			int MOVEMENT = 100;
			if (ptr->IsLeftEnd())
			{
				for (auto& ene : enemys_)
				{
					dir_ = 1;
					// ene->ChangeMoveDirRight();
					//ene->MovePosY(MOVEMENT);	
				}
				return;

			}
			if (ptr->IsRightEnd())
			{
				for (auto& ene : enemys_)
				{
					dir_ = -1;
					//ene->ChangeMoveDirLeft();
					//ene->MovePosY(MOVEMENT);
				}
				return;
			}
		}
	}
}

void Army::CheckEnemys()
{
	auto result = std::remove_if(enemys_.begin(), enemys_.end(),
		[](const GameObjectWeakPtr& obj) 
		{
			bool ret = true;
			if (auto ptr = obj.lock())
			{
				ret = !ptr->IsAlive();
			}
			return ret;
		});
	enemys_.erase(result, enemys_.end());
}

void Army::Assault()
{
	int idx = rand() % enemys_.size();

	if (auto ptr = enemys_[idx].lock())
	{
		ptr->OnNotify(Instruction::MOVE);
		ptr->OnNotify(Instruction::ATTACK);
		ptr->OnNotify(Instruction::WITHDRAWAL);
		ptr->OnNotify(Instruction::STANDBY);
	}
}

PointF Army::GetReturnPos(int ID)
{
	int row = ID / ENEMY_COL_SIZE;
	int col = ID % ENEMY_COL_SIZE;
	return PointF{ rect_.x + col * ENEMY_ALIGN_X, rect_.y + row * ENEMY_ALIGN_Y };
}


float func(float x)
{
	return x * x;
}

float derivative(float x)
{
	const float h = 0.001f;
	return func(x + h) - func(x) / h;
}

void a()
{
	float y = func(3.0f);
	float y1 = derivative(3.0f);

}