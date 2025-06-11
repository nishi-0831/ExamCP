#pragma once

#define test 0
//無名空間にあるのは後から外部ファイルで書き換えることが多い


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
#if test
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;
	const int ENEMY_NUM = ENEMY_COL_SIZE * ENEMY_ROW_SIZE;

	const int ENEMY_ALIGN_X = 50;
	const int ENEMY_ALIGN_Y = 50;

	const int ARMY_MARGIN = (WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COL_SIZE)) / 2;
#endif
}
extern float gDeltaTime;

enum Shooter
{
	PLAYER,
	ENEMY,
};
enum ETYPE
{
	ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};

//inlineを指定して直接展開
inline float GetDeltaTime()
{
	return gDeltaTime;
}

struct Point
{
	float x;
	float y;
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;
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