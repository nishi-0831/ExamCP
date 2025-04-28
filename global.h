#pragma once

//無名空間にあるのは後から外部ファイルで書き換えることが多い



const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;
extern float gDeltaTime;

//inlineを指定して直接展開
inline float GetDeltaTime()
{
	return gDeltaTime;
}

