#pragma once
#include "GameObject.h"
#include "global.h"
enum ETYPE
{
	ZAKO,MID,KNIGHT,BOSS,MAX_ETYPE
};
class Enemy :
    public GameObject
{
	int hImage_;//“G‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	float x_, y_;//“G‚ÌÀ•W
	float speed_;//“G‚ÌˆÚ“®‘¬“x
	int dir_;
	//bool isAlive_;//“G‚Ì¶€
	int ID_;//“G‚ÌID
	ETYPE type_;
public:
	Enemy(int id,ETYPE type);
	Enemy(int id);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x, y_ = y; }
	void SetID(int id) { ID_ = id; } //“G‚ÌID‚ğƒZƒbƒg
	
	bool IsLeftEnd();
	bool IsRightEnd();
	void ChangeMoveDirLeft();
	void ChangeMoveDirRight();

	Rect GetRect() const {
		return { x_, y_, ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT };
	}
};

