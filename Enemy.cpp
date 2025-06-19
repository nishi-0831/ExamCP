#include "Enemy.h"
#include "DxLib.h"
#include "global.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>
#include "Animation2D.h"
#include "Bullet.h"
#include "State.h"
#include "Lerp.h"
#include "Time.h"
#include <cmath>
#include "Army.h"
#include "Player.h"
namespace
{
#if test
	const int ENEMY_MARGIN_X = ENEMY_IMAGE_WIDTH / 2;
	const int ENEMY_MARGIN_Y = ENEMY_IMAGE_HEIGHT / 2;
	
	//const int ENEMY_COL_SIZE = 10;
	//const int ENEMY_ROW_SIZE = 7;
	
	const float ENEMY_INIT_SPEED = 100.0f; //初期移動速度
	const float ENEMY_INIT_X = 100.0f;//敵の初期X座標
	const float ENEMY_INIT_Y = 100.0f;//敵の初期Y座標

#endif	
	//攻撃後の隙
	const float attackWaitTime = 1.0f;
	enum MoveDir
	{
		left = -1,
		right = 1
	};
	PointF targetPos;
	Army* army;
	Player* player;
	float alignY = 150.0f;
}

Enemy::Enemy(int id, ETYPE type)
	: GameObject(), speed_(0), ID_(id),type_(type),dir_(1)
{
	timer_ = 0.0f;
	imageSize_ = { ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT };
	std::string imagePath[MAX_ETYPE] =
	{
		"Assets\\tiny_ship10.png", //ZAKO
		"Assets\\tiny_ship18.png",//MID
		"Assets\\tiny_ship16.png",//KNIGHT
		"Assets\\tiny_ship9.png",//BOSS
	};

	hImage_ = LoadGraph(imagePath[type_].c_str());
	
	if (hImage_ == -1)
	{
		//エラーを返してゲーム終了
	}

	/*x_ = ENEMY_INIT_X;
	y_ = ENEMY_INIT_Y;
	speed_ = ENEMY_INIT_SPEED;*/
	AddGameObject(this);
	//idとtypeを指定されなかったときの処理をここに書かねば(省略。書かない)

	shootOnce = false;
	lerp_ = new Lerp();
	eStates_ = {
		{Instruction::STANDBY, new State()},
		{Instruction::MOVE, new State()},
		{Instruction::ATTACK, new State()},
		{Instruction::WITHDRAWAL, new State()}
	};


	eStates_[Instruction::STANDBY]->SetInitialize([]() { });
	eStates_[Instruction::STANDBY]->SetBehavior([]() { });
	eStates_[Instruction::STANDBY]->SetExitCondition([]() {return true; });

	eStates_[Instruction::MOVE]->SetInitialize([this]() {this->SetMoveTarget(); });
	eStates_[Instruction::WITHDRAWAL]->SetInitialize([this]() {this->SetWithdrawTarget(); });
	eStates_[Instruction::ATTACK]->SetInitialize([]() { });

	eStates_[Instruction::ATTACK]->SetBehavior([this]() {this->UpdateAttack(); });
	eStates_[Instruction::MOVE]->SetBehavior([this]() {this->UpdateMove(); });
	eStates_[Instruction::WITHDRAWAL]->SetBehavior([this]() {this->UpdateWithdrawal(); });

	eStates_[Instruction::MOVE]->SetExitCondition([this]() {return this->lerp_->GetT() >= 1.0f; });
	eStates_[Instruction::WITHDRAWAL]->SetExitCondition([this]() {return this->lerp_->GetT() >= 1.0f; });
	eStates_[Instruction::ATTACK]->SetExitCondition([this]() {return this->timer_ >= attackWaitTime; });

	nowInstruction_ = Instruction::STANDBY;
	instructions_.push(Instruction::STANDBY);
}
Enemy::Enemy(int id, ETYPE type, float x, float y)
	:Enemy(id,type)
{
	timer_ = 0.0f;
	x_ = x;
	y_ = y;
	

}


Enemy::~Enemy()
{
	this->effect = new Effect(x_, y_);
	SetAlive(false);
	AddGameObject(this->effect);
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_);
	}
	
		for (auto& [key, state] : eStates_) {
			state->SetBehavior(nullptr);
			state->SetInitialize(nullptr);
			state->SetExitCondition(nullptr);
		}
	// ...既存のデストラクタ処理...
	
}

void Enemy::Update()
{
	float dt = GetDeltaTime();
	
	if ((instructions_.size() <= 1 && nowInstruction_ == Instruction::STANDBY )|| instructions_.empty())
	{
		return;
	}
	else if(first == true)
	{
		InitState();
		eStates_[instructions_.front()]->Initialize()();
		first = false;
	}
	eStates_[instructions_.front()]->GetBehavior()();
	if( eStates_[instructions_.front()]->GetExitCondition()() )
	{
		instructions_.pop();
		if (instructions_.empty())
		{
			return;
		}
		if (!eStates_.empty())
		{
			InitState();
			//if()
			eStates_[instructions_.front()]->Initialize()();
			nowInstruction_ = instructions_.front();
		}
		
	}
}

void Enemy::Draw()
{
	GameObject::Draw();
}

bool Enemy::IsLeftEnd()
{
	Rect rect = GetRect();
	return (rect.x < LEFT_END);
}

bool Enemy::IsRightEnd()
{
	//右(場外)にいったら～～
	Rect rect = GetRect();
	return (rect.width > RIGHT_END);
}

void Enemy::ChangeMoveDirLeft()
{
	dir_ = MoveDir::left;
}

void Enemy::ChangeMoveDirRight()
{
	//x_ = LEFT_END;
	dir_ = MoveDir::right;
}

void Enemy::MovePosY(float y)
{
	y_ += y;
}



void Enemy::OnNotify(Instruction instruction)
{
	instructions_.push(instruction);
}

void Enemy::InitState()
{
	lerp_->Reset();
	shootOnce = false;
	for (auto obj : gameObjects)
	{
		if (player != nullptr)
		{
			break;
		}
		player = dynamic_cast<Player*>(obj);
	}
	for (auto obj : gameObjects)
	{
		if (army != nullptr)
		{
			break;
		}
		army = dynamic_cast<Army*>(obj);
	}
}

void Enemy::SetMoveTarget()
{
	PointF target = player->GetPosF();
	alignY = 300.0f;
	PointF start = GetPosF();
	
	PointF end = PointF(target.x, target.y - alignY);

	//Enemyが真ん中より右か左かで軌道を変える
	float dir = 1.0f;
	float controlPointAlignX = 50.0f;
	float controlPointAlignY = 50.0f;

	//startの制御点
	PointF control1 = start;

	PointF control2 = end;

	//左
	if (start.x <= WIN_WIDTH / 2)
	{
		dir *= -1.0f;
	}

	control1.x = std::clamp(control1.x + (dir * controlPointAlignX), 0.0f, (float)WIN_WIDTH);
	control1.y = std::clamp(control1.y + (-controlPointAlignY), 0.0f, (float)WIN_HEIGHT);
	control2.x = std::clamp(control2.x + (dir * controlPointAlignX), 0.0f, (float)WIN_WIDTH);
	//control2.y = std::clamp(control2.y + ( -controlPointAlignY), 0.0f, (float)WIN_HEIGHT);


	lerp_->SetLoopMode(LoopMode::Once);
	lerp_->SetCubic(start, control1, control2, end);
	lerp_->SetDuration(3.0f);
}

void Enemy::SetWithdrawTarget()
{
	lerp_->SetLoopMode(LoopMode::Once);
	lerp_->SetLinear(GetPosF(), army->GetReturnPos(ID_));
	lerp_->SetDuration(2.0f);
}

void Enemy::SetAttackTarget(GameObject& target)
{
	targetPos = target.GetPosF();
}

void Enemy::UpdateMove()
{
	//lerp_->SetEnd(player->GetPosF()+PointF(0.0f,-alignY));
	lerp_->UpdateTime();
	PointF pos = lerp_->GetLerpPos();
	x_ = pos.x;
	y_ = pos.y;
}

void Enemy::UpdateAttack()
{
	if (!shootOnce)
	{
		PointF vec = player->GetPosF() - GetPosF();
		float Vsize = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
		PointF dir = vec / Vsize;
		AddGameObject(new Bullet(x_, y_, Shooter::ENEMY, dir));
		shootOnce = true;
	}
	timer_ += Time::DeltaTime();
}

void Enemy::UpdateWithdrawal()
{
	lerp_->UpdateTime();
	lerp_->SetEnd(army->GetReturnPos(ID_));
	PointF pos = lerp_->GetLerpPos();
	x_ = pos.x;
	y_ = pos.y;
}

void Enemy::UpdateTargetPos()
{

}
