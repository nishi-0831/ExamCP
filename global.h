#pragma once

//無名空間にあるのは後から外部ファイルで書き換えることが多い



const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;

const int PLAYER_IMAGE_WIDTH = 64; //画像の幅
const int PLAYER_IMAGE_HEIGHT = 64; //画像の高さ
const int ENEMY_IMAGE_WIDTH = 48; //画像の幅
const int ENEMY_IMAGE_HEIGHT = 48; //画像の高さ

extern float gDeltaTime;

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

	inline Point GetCenter() const
	{
		return { x + width / 2, y + height / 2 };
	}
};