#pragma once
#include <math.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#define test 0

enum GameState
{
	TITLE,
	PLAY,
	GAMEOVER
};
class Stage;
class GameObject;
// グローバル配列の型定義
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectWeakPtr = std::weak_ptr<GameObject>;
extern std::shared_ptr<Stage> stage;
extern GameState gameState;
extern std::vector<GameObjectPtr> gameObjects;
extern std::vector<GameObjectPtr> newObjects;

namespace
{

	
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;

	const int PLAYER_IMAGE_WIDTH = 64; //画像の幅
	const int PLAYER_IMAGE_HEIGHT = 64; //画像の高さ
	const int ENEMY_IMAGE_WIDTH = 48; //画像の幅
	const int ENEMY_IMAGE_HEIGHT = 48; //画像の高さ
	const int LEFT_END = 0;
	const int RIGHT_END = WIN_WIDTH;

}
extern float gDeltaTime;
enum class Instruction
{
	STANDBY,
	MOVE,
	ATTACK,
	WITHDRAWAL,
	INSTRUCTIONMAX
};

enum class Shooter
{
	PLAYER,
	ENEMY,
};
enum class ETYPE
{
	ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};

//inlineを指定して直接展開
inline float GetDeltaTime()
{
	return gDeltaTime;
}
inline void TransitionGameOver()
{
	
}
struct Point
{
	int x;
	int y;
	//aとbを足すよ
	Point operator+(const Point& rhs)
	{
		return Point{ x + rhs.x, y + rhs.y };
	}
	Point operator-(const Point& rhs)
	{
		return Point{ x - rhs.x, y - rhs.y };
	}
	Point operator*(const int rhs)
	{
		return Point{ x * rhs, y * rhs };
	}
	Point operator*(const Point rhs)
	{
		return Point{ x * rhs.x, y * rhs.y };
	}
	Point operator/(const int rhs)
	{
		return Point{ x / rhs, y / rhs };
	}
	Point operator/(const Point rhs)
	{
		return Point{ x / rhs.x, y / rhs.y };
	}
	Point operator+=(const Point& rhs)
	{
		return Point(x, y) + rhs;
	}
	Point operator-=(const Point& rhs)
	{
		return Point(x, y) - rhs;
	}
	static Point Add(Point a, Point b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}
	//aからbを引くよ
	static Point Sub(Point a, Point b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}
	static Point Abs(Point point)
	{
		return Point{ abs(point.x),abs(point.y) };
	}
	static int ManhattanDistance(Point a, Point b)
	{
		//2点 (x1, y1) と (x2, y2) 間のマンハッタン距離は、
		// |x1 - x2| + |y1 - y2| で計算されます
		return abs(a.x - b.x) + abs(a.y - b.y);
	}

};
struct PointF
{
	float x;
	float y;
	PointF()
	{
		x = 0;
		y = 0;
	}
	PointF(float f)
	{
		x = f;
		y = f;
	}
	PointF(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	//aとbを足すよ
#if 0
	
	PointF operator+(const PointF& rhs)
	{
		return PointF{ x + rhs.x, y + rhs.y };
	}
	PointF operator-(const PointF& rhs)
	{
		return PointF{ x - rhs.x, y - rhs.y };
	}
	PointF operator*(const float rhs)
	{
		return PointF{ x * rhs, y * rhs };
	}
	PointF operator*(const PointF rhs)
	{
		return PointF{ x * rhs.x, y * rhs.y };
	}
	PointF operator/(const float rhs)
	{
		return PointF{ x / rhs, y / rhs };
	}
	PointF operator/(const PointF rhs)
	{
		return PointF{ x / rhs.x, y / rhs.y };
	}
	PointF& operator+=(const PointF& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	PointF& operator-=(const PointF& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	static PointF Add(PointF a, PointF b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}
	//aからbを引くよ
	static PointF Sub(PointF a, PointF b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}
#endif
	

};
//名前空間で囲んだ方がいい
#if 1
	inline PointF operator+(const PointF& lhs,const PointF& rhs)
	{
		return PointF{ lhs.x + rhs.x, lhs.y + rhs.y };
	}
	inline PointF operator-(const PointF& lhs,const PointF& rhs)
	{
		return PointF{ lhs.x - rhs.x, lhs.y - rhs.y };
	}
	inline PointF operator*(const PointF& lhs,const float rhs)
	{
		return PointF{ lhs.x * rhs, lhs.y * rhs };
	}
	inline PointF operator*(const PointF& lhs,const PointF rhs)
	{
		return PointF{ lhs.x * rhs.x, lhs.y * rhs.y };
	}
	inline PointF operator/(const PointF& lhs,const float rhs)
	{
		return PointF{ lhs.x / rhs, lhs.y / rhs };
	}
	inline PointF operator/(const PointF& lhs,const PointF rhs)
	{
		return PointF{ lhs.x / rhs.x, lhs.y / rhs.y };
	}
	inline PointF operator+=(const PointF& lhs,const PointF& rhs)
	{
		PointF ret;
		ret.x = lhs.x + rhs.x;
		ret.y = lhs.y + rhs.y;
		return ret;
	}
	inline PointF operator-=(const PointF& lhs,const PointF& rhs)
	{
		PointF ret;
		ret.x = lhs.x - rhs.x;
		ret.y = lhs.y - rhs.y;
		return ret;
	}

#endif
struct Rect
{
	float x;
	float y;
	float width;
	float height;
    inline Point GetCenter()
    {
        return Point{ static_cast<int>(x + ((width - x) / 2)), static_cast<int>(y + ((height - y) / 2)) };
    }
};

inline bool IntersectRect(const Rect& a, const Rect& b)
{
	//aとbがぶつかっているならtrue
	/*if (a.y < b.y + b.height && a.y + a.height > b.y && a.x + a.width > b.x && a.x < b.x + b.width)
	{
		return true;
	}*/
	if (a.y <b.height && a.height > b.y && a.width > b.x && a.x < b.width)
	{
		return true;
	}
	/*Point centerA = a.GetCenter();
	Point centerB = b.GetCenter();

	Point hitLength = { (a.width / 2) + (b.width / 2),(a.height / 2) + (b.height / 2) };
	Point absDis = {abs( centerA.x - centerB.x),abs(centerA.y - centerB.y) };

	if ((hitLength.x < absDis.x) && (hitLength.y < absDis.y))
	{
		return true;
	}*/

	return false;
}