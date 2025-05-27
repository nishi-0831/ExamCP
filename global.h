#pragma once

//������Ԃɂ���̂͌ォ��O���t�@�C���ŏ��������邱�Ƃ�����



const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;

const int PLAYER_IMAGE_WIDTH = 64; //�摜�̕�
const int PLAYER_IMAGE_HEIGHT = 64; //�摜�̍���
const int ENEMY_IMAGE_WIDTH = 48; //�摜�̕�
const int ENEMY_IMAGE_HEIGHT = 48; //�摜�̍���

extern float gDeltaTime;

//inline���w�肵�Ē��ړW�J
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