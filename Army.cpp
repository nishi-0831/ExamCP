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
namespace
{
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;
	const int ENEMY_NUM = 10;
	//const int ENEMY_NUM = ENEMY_COL_SIZE * ENEMY_ROW_SIZE;

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

	static int radius = 10;
	static int tx = 180;
	static int ty = 180;
	static int degree = 0;

	std::vector<Point> table;
	//lerp lerpPos;
	int x = WIN_WIDTH / 3;
	int y = WIN_HEIGHT / 3;

	int idx = 0;
	
	const float targetInterval = 2.0f;
	float targetTimer = 0.0f;
	Point p1;
	const float LEN = 10.0f;

	const float lTimer = 0.0f;

	float drag = 0;
	float spring = 2.0f;
		
}

Army::Army()
{
	p1 = { 10,0 };
	for (int i = 0; i < 9; i++)
	{
		int col = i % 3 + 1;
		int row = i / 3 + 1;
		Point pos{ (x * col)/2,(y * row)/2 };
		table.push_back(pos);
	}
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
	rect_.width += rect_.x;

	targetTimer += Time::DeltaTime();
	if (targetTimer >= targetInterval)
	{
		idx = ++idx % table.size();
		targetTimer = 0;
	}


	degree++;
	double radian = M_PI * degree / 180;
	
	Point target = table[idx];
	static float posX = 0;
	static float posY = 0;
	static PointF p1 = { 0,0 };

	p1 += (PointF{ (float)target.x,(float)target.y } - PointF{ posX, posY }) * spring * Time::DeltaTime();
	p1 -= p1 * drag * Time::DeltaTime();

	posX += p1.x * Time::DeltaTime();
	posY += p1.y * Time::DeltaTime();
	
	DrawCircle(posX, posY, radius, GetColor(122, 122, 122), FALSE);
#if 0
	
#endif
}

void Army::Draw()
{
	DrawBox(rect_.x, rect_.y, rect_.width, rect_.height, GetColor(0, 255, 0), FALSE);
	ImGui::Begin("Army");
	ImGui::Text("idx:%d", idx);
	Point center = rect_.GetCenter();
	DrawCircle(center.x, center.y, 5, GetColor(255, 0, 0),TRUE);
	ImGui::Text("rect(%f,%f)", rect_.x, rect_.y);
	ImGui::BeginChild("enemy");
	for (int i = 0; i < enemys_.size();i++)
	{
		ImGui::Text("Army%d:(%f,%f)", i, enemys_[i]->x_, enemys_[i]->y_);
	}
	ImGui::EndChild();
	ImGui::End();
	for (auto t : table)
	{
		DrawCircle(t.x, t.y, 5, GetColor(255, 0, 0), TRUE);
	}
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