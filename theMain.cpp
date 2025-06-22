#define _USE_MATH_DEFINES
#include "DxLib.h"
#include  <math.h>
#include "global.h"
#include "Input.h"
#include <vector>
#include "Stage.h"
#include "Time.h"
#include "ImGui/imgui_impl_dxlib.hpp"
#include "GameObject.h"
#include <memory>
class GameObject;
class Stage;

namespace
{
	const int BGCOLOR[3] = {0,0, 0}; // �w�i�F
	int crrTime;
	int prevTime;

	
	
	//Stage* stage;
}
std::shared_ptr<Stage> stage;
GameState gameState;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectWeakPtr = std::weak_ptr<GameObject>;

#if 0
std::vector<GameObject*> gameObjects; //�Q�[���I�u�W�F�N�g�̃x�N�^�[
std::vector<GameObject*> newObjects;
#endif
std::vector<GameObjectPtr> gameObjects; //�Q�[���I�u�W�F�N�g�̃x�N�^�[
std::vector<GameObjectPtr> newObjects;

float gDeltaTime = 0.0f;//�t���[���Ԃ̎��ԍ�
void UpdatePlay();
void UpdateTitle();
void UpdateGameOver();
void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0], BGCOLOR[1], BGCOLOR[2]);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "�E�B���h�E�̃e�X�g");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	
	crrTime = GetNowCount();
	prevTime = GetNowCount();
	
	gameState = GameState::PLAY;
	//Stage* stage = new Stage();
	stage = GameObject::CreateGameObject<Stage>();
	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
		{
			// DxLib��ImGui�̃E�B���h�E�v���V�[�W���𗼗�������
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

		switch (gameState)
		{
		case GameState::TITLE:
				UpdateTitle();
				break;
		case GameState::PLAY:
			UpdatePlay();
			break;
		case GameState::GAMEOVER:
			UpdateGameOver();
			break;
		}
#if 0
		//�����ɂ�肽������������(��������)
		if (newObjects.size() > 0)
		{
			for (auto& obj : newObjects)
			{
				gameObjects.push_back(obj); //�V�����Q�[���I�u�W�F�N�g��ǉ�
			}
			newObjects.clear();
		}

		//gameObjects�̍X�V
		for (auto& obj : gameObjects)
		{
			obj->Update();
		}

		//gameObjects�̕`��
		for (auto& obj : gameObjects)
		{
			obj->Draw();
		}

		
		//drawBezier.Update();
		//drawBezier.Draw();
		

		

		for (auto it = gameObjects.begin(); it != gameObjects.end();)
		{
			if (!(*it)->IsAlive()) //�����Ă��Ȃ��I�u�W�F�N�g���폜
			{
				delete* it;
				it = gameObjects.erase(it);
			}
			else
			{
				++it;
			}
		}
		
		
#endif
		//�����ɂ�肽������������(�����܂�)
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDXlib_RenderDrawData();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
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

void UpdateTitle()
{
	static int hImage = LoadGraph("Assets/title.png");
	DrawGraph(0, 0, hImage, TRUE);
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		gameState = GameState::PLAY;
		for (auto& obj : gameObjects) {
			obj->SetActive(false);
		}
		for (auto& obj : newObjects) {
			obj->SetActive(false);
		}
		gameObjects.clear();
		newObjects.clear();
		stage = GameObject::CreateGameObject<Stage>();
		//stage = new Stage();
	}
}

void UpdatePlay()
{
#if 1
	//�����ɂ�肽������������(��������)
	if (!newObjects.empty())
	{
		gameObjects.insert(gameObjects.end(), newObjects.begin(), newObjects.end());
		newObjects.clear();
	}

	//�����Ă���O�ɋl�߂āA����ł��̐擪�̃C�e���[�^��Ⴄ
	auto result = std::remove_if(gameObjects.begin(), gameObjects.end(),
		[](const GameObjectPtr& obj) {return !obj->IsAlive(); });
	//�����I�ɉ�����ׂ�
	gameObjects.erase(result,gameObjects.end());

	//gameObjects�̍X�V
	for (auto& obj : gameObjects)
	{
		obj->Update();
	}

	//gameObjects�̕`��
	for (auto& obj : gameObjects)
	{
		obj->Draw();
	}
#endif

	

	
}

void UpdateGameOver()
{
	static int hImage = LoadGraph("Assets/gameOver.png");
	DrawGraph(0, 0, hImage, TRUE);
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		gameState = GameState::TITLE;
	}
}

