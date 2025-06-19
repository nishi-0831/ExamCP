#pragma once
#include "GameObject.h"
#include "global.h"
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <queue>
#include <vector>
class State;
class Effect;
class Army;
class Lerp;
//enum ETYPE
//{
//	ZAKO,MID,KNIGHT,BOSS,MAX_ETYPE
//};


class Enemy :
    public GameObject
{
	friend Army; 
public:
	Enemy(int id,ETYPE type);
	//Enemy(int id);
	Enemy(int id, ETYPE type, float x, float y);
	//Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x, y_ = y; }
	Point GetPos() { return Point(x_, y_); }
	void SetID(int id) { ID_ = id; } //ìGÇÃIDÇÉZÉbÉg
	int GetID() { return ID_; }
	bool IsLeftEnd();
	bool IsRightEnd();
	void ChangeMoveDirLeft();
	void ChangeMoveDirRight();

	void MovePosY(float y);
	void SetAlive(bool flag) { isAlive_ = flag; }


	///
	//void OnNotify(GameObject& obj, Instruction instruction);
	
	void OnNotify(Instruction instruction);
	//void Initialize();
	void ProcessTask();
protected:
private:
	
	bool first = true;
	Effect* effect;
	std::queue<Instruction> instructions_;
	Instruction nowInstruction_;
	std::unordered_map<Instruction, State*> eStates_;

	float speed_;//ìGÇÃà⁄ìÆë¨ìx

	bool shootOnce;
	float timer_;
	//PointF targetPos_;
	int dir_;
	//bool isAlive_;//ìGÇÃê∂éÄ
	int ID_;//ìGÇÃID
	ETYPE type_;
	Lerp* lerp_;
	///
	void InitState();
	void SetMoveTarget();
	void SetWithdrawTarget();
	void SetAttackTarget(GameObject& target);
	void UpdateMove();
	void UpdateAttack();
	void UpdateWithdrawal();

	void UpdateTargetPos();
};

