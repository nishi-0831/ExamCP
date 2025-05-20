#pragma once
#include <vector>
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

extern std::vector<GameObject*> gameObjects; //ゲームオブジェクトのベクター
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj)
{
	newObjects.push_back(obj);//ゲームオブジェクトをベクターに追加
}


