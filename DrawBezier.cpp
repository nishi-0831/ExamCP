#include "DrawBezier.h"
#include "global.h"
#include "Input.h"
#include "DxLib.h"
#include "Time.h"
#include "ImGui/imgui.h"
#include <vector>

#if 0
namespace
{
	float half = WIN_WIDTH / 2;
	PointF start = { half + (half / 2),300 };
	//PointF start = { half,WIN_HEIGHT - 100};
	//PointF start = { half - (half/2),WIN_HEIGHT/2};
	PointF end = { half,WIN_HEIGHT - 100 };
	//PointF end = { half + (half/2),300};

	float alignX = 100.0f;
	PointF controlPos1 = end + PointF{alignX,-100};
	PointF controlPos2 = start + PointF{ -alignX,-100 };
	//PointF controlPos2 = {WIN_WIDTH / 2, WIN_HEIGHT };

	float duration = 1.0f;
	float r = 10.0f;

	int interpolNum = 10;
	int followNum = 1;
	std::vector<PointF> interpolPos;

	float interval = 0.4f;

	std::vector<Lerp*> followLerp;
	std::vector<PointF> followCircle;

	bool isReverse = false;

	PointF pos;
	Point mousePos;

	bool isDrag1 = false;
	bool isDrag2 = false;
	static float timer = 0.0f;
}



DrawBezier::DrawBezier()
{
	//start = { 0,0 };
	//end = { WIN_WIDTH,WIN_HEIGHT };

	
	interpolPos.resize(interpolNum);
	followCircle.resize(followNum);
	followLerp.resize(followNum);
	AddGameObject(this);
	//lerp.SetLinear(start,end);
	//lerp.SetQuadratic(start,controlPos1,end);
	lerp_.SetCubic(start,controlPos1,controlPos2,end);
	lerp_.SetDuration(duration);
	lerp_.Init();
	lerp_.SetLoopMode(LoopMode::Loop);

	
}

void DrawBezier::Update()
{
	MoveControlPos();
	
	static int idx = 0;
	timer += Time::DeltaTime();
	//ImGui::Text("%f", timer);
	if (idx < followNum)
	{
		if (timer > interval)
		{
			timer -= interval;

			followLerp[idx] = new Lerp();

			*followLerp[idx] = lerp_;
			idx++;
		}
	}
	
	for (int i = 0; i < idx;i++)
	{
		if (followLerp[i] != nullptr)
		{
			LerpUpdate(followLerp[i],i);
		}
	}

	lerp_.SetCubic(start, controlPos1, controlPos2, end);
	float t = 1.0f / ((float)interpolNum + 1);
	for (int i = 0; i < interpolNum; i++)
	{
		interpolPos[i] = lerp_.GetLerpPos(t + (t * i));
	}
}

void DrawBezier::LerpUpdate()
{
#if 0
	lerp.SetCubic(start, controlPos1, controlPos2, end);
	float t = 1.0f / ((float)interpolNum + 1);

	lerp.UpdateTime();


	for (int i = 0; i < interpolNum; i++)
	{
		interpolPos[i] = lerp.GetLerpPos(t + (t * i));
	}

	//‚±‚Ìpos‚É’Ç]‚·‚é‰~‚ð‘‚­
	pos = lerp.GetLerpPos();
	int dir = lerp.GetDir();

	if (dir == 1)
	{
		lerp.SetCubic(start, controlPos1, controlPos2, pos);
	}
	else if (dir == -1)
	{
		lerp.SetCubic(end, controlPos1, controlPos2, start);
	}

	float followT = lerp.GetT() / ((float)followNum + 1);
	//dir‚ª•Ï‚í‚é‚Æfollow‚ÌˆÊ’u‚Í‹}•Ï‚·‚é
	//‚½‚¾’Ç]‚Æ‚¢‚¤‚æ‚è’x‚ê‚Ä‚·‚·‚ÞŠ´‚¶‚É‚µ‚½‚Ù‚¤‚¢‚¢‚©‚à

	//’Ç]‰~ˆê‚Âˆê‚Â‚ÉLerpƒIƒuƒWƒFƒNƒg‚ð•t‚¯‚é
	//0.2•b‚²‚Æ‚É¶¬‚µ‚Ä‚Ý‚é
	//‚ ‚ç‚©‚¶‚ßLerp‚ÌÝ’è‚ðŽæ‚Á‚Ä‚¨‚¢‚ÄA’x‚ê‚Ä¶¬
	for (int i = 0;i < followNum;i++)
	{
		followCircle[i] = lerp.GetLerpPos(followT + (followT * i));
	}
#endif
}

void DrawBezier::LerpUpdate(Lerp* lerp, int index)
{
	lerp->SetCubic(start, controlPos1, controlPos2, end);
	lerp->UpdateTime();
	followCircle[index] = lerp->GetLerpPos();
}



void DrawBezier::Draw()
{
	int startCol = GetColor(255, 0, 0);
	int endCol  = GetColor(0, 255, 0);
	int polCol = GetColor(255, 255, 255);
	int con1 = GetColor(255, 0, 0);
	int con2 = GetColor(0, 255, 0);
	int lineCol = GetColor(0, 0, 255);
	DrawCircle(start.x, start.y, r, startCol, TRUE);

	DrawLine(start.x, start.y, controlPos1.x, controlPos1.y, polCol);
	ImGui::Text("controlPos1:%f,%f", controlPos1.x, controlPos1.y);
	DrawLine(end.x, end.y, controlPos2.x, controlPos2.y, polCol);

	DrawCircle(end.x, end.y, r, endCol, TRUE);
	DrawCircle(controlPos1.x, controlPos1.y, r, con1, TRUE);
	DrawCircle(controlPos2.x, controlPos2.y, r, con2, TRUE);
	for (auto pos : interpolPos)
	{
		//DrawCircle(pos.x, pos.y, r, polCol);
	}
	int i = 0;
	for (auto fol : followCircle)
	{
		i++;
		ImGui::Text("%d : %4.1f,%4.1f",i, fol.x,fol.y);
		DrawCircle(fol.x, fol.y, r, polCol);
	}
	DrawLine(start.x, start.y, end.x, end.y, lineCol);
	DrawCircle(pos.x, pos.y, r, GetColor(255, 255, 255));
	//ImGui::Text("%f", lerp_.GetTimer());
	//ImGui::Text("pos:%f,%f", pos.x,pos.y);
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

#endif