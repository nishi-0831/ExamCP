#pragma once
#include "GameObject.h"
#include "global.h"
class Effect;
enum ETYPE
{
	ZAKO,MID,KNIGHT,BOSS,MAX_ETYPE
};
class Enemy :
    public GameObject
{
public:
	Enemy(int id,ETYPE type);
	Enemy(int id);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x, y_ = y; }
	Point GetPos() { return Point(x_, y_); }
	void SetID(int id) { ID_ = id; } //“G‚ÌID‚ğƒZƒbƒg
	int GetID() { return ID_; }
	bool IsLeftEnd();
	bool IsRightEnd();
	void ChangeMoveDirLeft();
	void ChangeMoveDirRight();

	void MovePosY(float y);
	void SetAlive(bool flag) { isAlive_ = flag; }
protected:
private:
	Effect* effect;
	
	float speed_;//“G‚ÌˆÚ“®‘¬“x
	int dir_;
	//bool isAlive_;//“G‚Ì¶€
	int ID_;//“G‚ÌID
	ETYPE type_;
	
};

