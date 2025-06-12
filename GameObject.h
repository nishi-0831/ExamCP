#pragma once
#include <vector>
#include "global.h"
class GameObject
{
protected:
	bool isAlive_;
	Point imageSize_;
	int hImage_;
	float x_,y_;
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() ;
	bool IsAlive() const { return isAlive_; } //�����m�F
	void SetActive(bool alive) { isAlive_ = alive; }
	Rect GetRect();
	Point GetImageCenter();
	Point GetPos() { return Point(x_, y_); }
};

extern std::vector<GameObject*> gameObjects; //�Q�[���I�u�W�F�N�g�̃x�N�^�[
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj)
{
	newObjects.push_back(obj);//�Q�[���I�u�W�F�N�g���x�N�^�[�ɒǉ�
}


