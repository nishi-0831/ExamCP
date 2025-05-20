#pragma once
#include <vector>
class GameObject
{
protected:
	bool isAlive_;
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool IsAlive() const { return isAlive_; } //生存確認
};

extern std::vector<GameObject*> gameObjects; //ゲームオブジェクトのベクター
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj)
{
	newObjects.push_back(obj);//ゲームオブジェクトをベクターに追加
}


