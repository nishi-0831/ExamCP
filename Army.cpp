#define _USE_MATH_DEFINES
#include "Army.h"
#include "Enemy.h"
#include "global.h"
#include <DxLib.h>
#include "Time.h"
#include "Bullet.h"
#include  <math.h>
#include "ImGui/imgui.h"
namespace
{
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;
	const int ENEMY_NUM = ENEMY_COL_SIZE * ENEMY_ROW_SIZE;

	const int ENEMY_ALIGN_X = 50;
	const int ENEMY_ALIGN_Y = 50;

	//矩形領域
	const int ARMY_RECT_X = (WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COL_SIZE)) / 2;
	const int ARMY_RECT_WIDTH = WIN_WIDTH - ARMY_RECT_X;
	const int ARMY_RECT_Y = (WIN_HEIGHT - (ENEMY_ALIGN_Y * ENEMY_ROW_SIZE)) / 2;
	const int ARMY_RECT_HEIGHT = WIN_HEIGHT - ARMY_RECT_Y;

	const int ENEMY_MARGIN_X = ENEMY_IMAGE_WIDTH / 2;
	const int ENEMY_MARGIN_Y = ENEMY_IMAGE_HEIGHT / 2;

	const float ENEMY_INIT_SPEED = 100.0f; //初期移動速度
	const float ENEMY_INIT_X = 100.0f;//敵の初期X座標
	const float ENEMY_INIT_Y = 100.0f;//敵の初期Y座標

	////
	const int ARMY_INIT_X = 100.0f;
	const int ARMY_INIT_Y = 100.0f;

	const float shootInterval = 0.5f;

	int rightEnd = ENEMY_ROW_SIZE;

	static int radius = 300;
	static int tx = 180;
	static int ty = 180;
	static int degree = 0;
}

Army::Army()
{
	rect_.x = ARMY_RECT_X;
	rect_.y = ARMY_RECT_Y;
	rect_.width = ARMY_RECT_WIDTH;
	rect_.height = ARMY_RECT_HEIGHT;
	dir_ = 1;
	speed_ = 100.0f;
	shootTimer_ = 0.0f;
	//enemys_ = std::vector<Enemy*>(ENEMY_NUM);
	enemys_.resize(ENEMY_NUM);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//MAX_ETYPEで割った余りはMAX_ETYPE未満になるよ
		//enemys_[i] = new Enemy(i,(ETYPE)(i % MAX_ETYPE));
		//enemys_[i]->SetID(i);
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
		//enemys_[i] = new Enemy(i, type);
		enemys_[i] = new Enemy(i, enemyType[row]);
		enemys_[i]->SetID(i);
		enemys_[i]->SetPos(rect_.x + col * ENEMY_ALIGN_X, rect_.y + row * ENEMY_ALIGN_Y);
	}
}


Army::~Army()
{
}

void Army::Update()
{
	//射撃
	shootTimer_ += GetDeltaTime();
	if (shootTimer_ >= shootInterval)
	{
		Point point = enemys_[rand() % ENEMY_NUM]->GetPos();
		AddGameObject(new Bullet(point.x, point.y, Shooter::ENEMY));
		shootTimer_ -= shootInterval;
	}
	//移動
	float dt = Time::DeltaTime();
	rect_.x += dt * speed_ * dir_;

	degree++;
	double radian = M_PI * degree / 180;

	for (int i = 0; i < enemys_.size();i++)
	{
		int row = i / ENEMY_COL_SIZE;
		int col = i % ENEMY_COL_SIZE;
		int x = rect_.x + radius * cos(M_PI * (degree + i) / tx );
		int y = rect_.y + radius * sin(M_PI * (degree + i) / ty );
		enemys_[i]->SetPos(x,y);
		//enemys_[i]->SetPos(rect_.x + col * ENEMY_ALIGN_X, rect_.y + row * ENEMY_ALIGN_Y);
	}
#if 0
	ImGui::Begin("circle");
	ImGui::Text("degree%d", degree);
	ImGui::Text("degree%lf", radian);

	DrawCircle(WIN_WIDTH / 2, WIN_HEIGHT / 2, radius, GetColor(122, 122, 122), FALSE);
	
	ImGui::InputInt("tx", &tx);
	ImGui::InputInt("tx", &ty);

	for (int i = 0;i <= 180;i += 30)
	{
		int x = WIN_WIDTH / 2 + radius * cos(M_PI * (degree + i) / (tx + 1));
		int y = WIN_HEIGHT / 2 + radius * sin(M_PI * (degree + i) / (ty + 1));
		DrawCircle(x, y, 20, GetColor(0, 255, 255));

	}

	ImGui::End();
#endif
}

void Army::Draw()
{
	DrawBox(rect_.x, rect_.y, rect_.width, rect_.height, GetColor(0, 255, 0), FALSE);
	ImGui::Begin("Army");

	Point center = Point{ rect_.x+ ((rect_.width - rect_.x) / 2),rect_.y+((rect_.height - rect_.y) / 2) };
	//Point center = Point{ rect_.x + (rect_.width / 2),rect_.y + (rect_.height / 2) };
	DrawCircle(center.x, center.y, 5, GetColor(255, 0, 0),TRUE);
	//ImGui::Text()
	ImGui::BeginChild("enemy");
	for (int i = 0; i < enemys_.size();i++)
	{
		ImGui::Text("Army%d:(%f,%f)", i, enemys_[i]->x_, enemys_[i]->y_);
	}
	ImGui::EndChild();
	ImGui::End();
}

void Army::IsOutOfScreen()
{
	for (auto& e : enemys_)
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
			for (auto& ene : enemys_)
			{
				ene->ChangeMoveDirRight();
				//ene->MovePosY(MOVEMENT);	
			}
			return;

		}
		if (e->IsRightEnd())
		{
			for (auto& ene : enemys_)
			{
				ene->ChangeMoveDirLeft();
				//ene->MovePosY(MOVEMENT);
			}
			return;
		}
	}
}


