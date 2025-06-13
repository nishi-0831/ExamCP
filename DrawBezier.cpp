#include "DrawBezier.h"
#include "global.h"
#include "Input.h"
#include "DxLib.h"
#include "Time.h"
#include "ImGui/imgui.h"
#include <vector>
namespace
{
	PointF start = { 0,0 };
	PointF end = { WIN_WIDTH,WIN_HEIGHT };

	PointF controlPos1 = { WIN_WIDTH / 2,0 };
	PointF controlPos2 = {WIN_WIDTH / 2, WIN_HEIGHT };

	float duration = 1.0f;
	float r = 10.0f;

	int interpolNum = 10;
	std::vector<PointF> interpolPos;

	bool isReverse = false;

	PointF pos;
	Point mousePos;

	bool isDrag1 = false;
	bool isDrag2 = false;
}



DrawBezier::DrawBezier()
{
	start = { 0,0 };
	end = { WIN_WIDTH,WIN_HEIGHT };

	controlPos1 = { WIN_WIDTH / 2,0 };
	interpolPos.resize(interpolNum);
	AddGameObject(this);
	//lerp.SetLinear(start,end);
	//lerp.SetQuadratic(start,controlPos1,end);
	lerp.SetCubic(start,controlPos1,controlPos2,end);
	lerp.SetDuration(duration);
	lerp.SetReverse(true);
	lerp.SetLoop(true);
}

void DrawBezier::Update()
{
	MoveControlPos();
	lerp.SetCubic(start, controlPos1, controlPos2, end);
	float t = 1.0f / ((float)interpolNum + 1);
	for (int i = 0; i < interpolNum; i++)
	{
		interpolPos[i] = lerp.GetLerpPos(t + (t * i));
	}

	lerp.UpdateTime();
	pos = lerp.GetLerpPos();
}

void DrawBezier::Draw()
{
	int startCol = GetColor(255, 0, 0);
	int endCol  = GetColor(0, 255, 0);
	int polCol = GetColor(255, 255, 255);
	int lineCol = GetColor(0, 0, 255);
	DrawCircle(start.x, start.y, r, startCol, TRUE);
	DrawCircle(end.x, end.y, r, endCol, TRUE);
	DrawCircle(controlPos1.x, controlPos1.y, r, polCol, TRUE);
	DrawCircle(controlPos2.x, controlPos2.y, r, polCol, TRUE);
	for (auto pos : interpolPos)
	{
		DrawCircle(pos.x, pos.y, r, polCol);
	}
	DrawLine(start.x, start.y, end.x, end.y, lineCol);
	DrawCircle(pos.x, pos.y, r, GetColor(255, 255, 255));
	ImGui::Text("%f", lerp.GetTimer());
	ImGui::Text("%f,%f", pos.x,pos.y);
}

void DrawBezier::MoveControlPos()
{
	if (Input::IsButtonKeep(Input::Mouse::LEFT))
	{
		if (Input::IsInCircle(controlPos1.x, controlPos1.y, r))
		{
			
			isDrag1 = true;
		}
	}
	else
	{
		isDrag1 = false;
	}
	if (isDrag1)
	{
		int x = Input::GetMouseX();
		int y = Input::GetMouseY();
		controlPos1.x = x;
		controlPos1.y = y;
	}
	if (Input::IsButtonKeep(Input::Mouse::LEFT))
	{
		if (Input::IsInCircle(controlPos2.x, controlPos2.y, r))
		{
			
			isDrag2 = true;
		}
	}
	else
	{
		isDrag2 = false;
	}
	if (isDrag2)
	{
		int x = Input::GetMouseX();
		int y = Input::GetMouseY();
		controlPos2.x = x;
		controlPos2.y = y;
	}
}
