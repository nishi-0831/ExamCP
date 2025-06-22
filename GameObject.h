#pragma once
#include <vector>
#include "global.h"
#include <utility>
class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
	bool isAlive_;
	Point imageSize_;
	int hImage_;
	float x_,y_;
	GameObject* parent_;
	GameObject* child_;

	static void AddGameObject(std::shared_ptr<GameObject> obj)
	{
		newObjects.push_back(obj);
	}
	

	
public:
	template<typename T, typename... Args>
	static std::shared_ptr<T> CreateGameObject(Args&&... args);
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() ;
	bool IsAlive() const { return isAlive_; } //生存確認
	void SetActive(bool alive) { isAlive_ = alive; }
	Rect GetRect();
	Point GetImageCenter();
	Point GetPos() { return Point(x_, y_); }
	PointF GetPosF() { return PointF(x_, y_); }
};

template<typename T, typename... Args>
static std::shared_ptr<T> GameObject::CreateGameObject(Args&&... args)
{
	auto obj = std::make_shared<T>(std::forward<Args>(args)...);
	AddGameObject(obj);
	return obj;
}
#if 0
inline void AddGameObject(GameObject* obj)
{
	newObjects.push_back(obj);//ゲームオブジェクトをベクターに追加
}
#endif




