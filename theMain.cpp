#define _USE_MATH_DEFINES
#include "DxLib.h"
#include  <math.h>
#include "global.h"
#include "Input.h"
#include <vector>
#include "Stage.h"
#include "Time.h"
#include "ImGui/imgui_impl_dxlib.hpp"
#include "DrawBezier.h"
namespace
{
	const int BGCOLOR[3] = {0,0, 0}; // 背景色
	int crrTime;
	int prevTime;
	DrawBezier drawBezier;
}

std::vector<GameObject*> gameObjects; //ゲームオブジェクトのベクター
std::vector<GameObject*> newObjects;

float gDeltaTime = 0.0f;//フレーム間の時間差

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0], BGCOLOR[1], BGCOLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	
	crrTime = GetNowCount();
	prevTime = GetNowCount();
	
	Stage* stage = new Stage();
	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
		{
			// DxLibとImGuiのウィンドウプロシージャを両立させる
			SetUseHookWinProcReturnValue(FALSE);
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		});
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());	ImGui_ImplDXlib_Init();
	Time::Init();
	
	while (true)
	{
		ImGui_ImplDXlib_NewFrame();
		ImGui::NewFrame();

		Time::Refresh();
		ClearDrawScreen();
		Input::KeyStateUpdate();

		crrTime = GetNowCount();

		float deltaTime = (crrTime - prevTime) / 1000.0f;
		gDeltaTime = deltaTime;
		prevTime = crrTime;
#if 0
		//ここにやりたい処理を書く(ここから)
		if (newObjects.size() > 0)
		{
			for (auto& obj : newObjects)
			{
				gameObjects.push_back(obj); //新しいゲームオブジェクトを追加
			}
			newObjects.clear();
		}

		//gameObjectsの更新
		for (auto& obj : gameObjects)
		{
			obj->Update();
		}

		//gameObjectsの描画
		for (auto& obj : gameObjects)
		{
			obj->Draw();
		}
#endif
		
		drawBezier.Update();
		drawBezier.Draw();
		

		

		for (auto it = gameObjects.begin(); it != gameObjects.end();)
		{
			if (!(*it)->IsAlive()) //生きていないオブジェクトを削除
			{
				delete* it;
				it = gameObjects.erase(it);
			}
			else
			{
				++it;
			}
		}
		
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDXlib_RenderDrawData();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		//ここにやりたい処理を書く(ここまで)

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}
	ImGui_ImplDXlib_Shutdown();
	ImGui::DestroyContext();
	DxLib_End();
	return 0;
}