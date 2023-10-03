#pragma once
#include "Task_StageSelect.h"
namespace StageSelect
{
	Object::Object(CManager* pManager) : BTask(pManager)//コンストラクタ
	{
		this->menu = Menu::Non;
		this->page = 1;

		graphic[0] = LoadGraph("./data/image/Stage1Book.png");
		graphic[1] = LoadGraph("./data/image/Stage2Book.png");
		graphic[2] = LoadGraph("./data/image/StageExitBook.png");
	}
	Object::~Object()
	{
	}
	void Object::Update()
	{
		zoom = -20;
		zoom2 = -20;
		zoom3 = -20;
		GetMousePoint(&mx, &my);
		mouse = GetMouseInput();
		if (mx > 280+zoom && mx + 2 < 380+zoom && my > 80+zoom && my + 2 < 210 + zoom)
		{
			zoom = 0;
			if (mouse & MOUSE_INPUT_LEFT)
			{
				//ステージ1にシーン移行
				ge->gamestage = MyGE::MyGameEngine::GameStage::stage1;
				manager->scene = new GameIntro::Object(manager);
				delete this;
			}
		}

		if (mx > 380+zoom2 && mx + 2 < 480+zoom2 && my > 80+zoom2 && my + 2 < 210 + zoom2)
		{
			zoom2 = 0;
			if (mouse & MOUSE_INPUT_LEFT)
			{
				//ステージ2にシーン移行
				ge->gamestage = MyGE::MyGameEngine::GameStage::stage2;
				manager->scene = new GameIntro::Object(manager);
				delete this;
			}
		}
		if (mx > 480 + zoom3 && mx + 2 < 580 + zoom3 && my > 80 + zoom3 && my + 2 < 210 + zoom3)
		{
			zoom3 = 0;
			if (mouse & MOUSE_INPUT_LEFT)
			{
				//ステージ2にシーン移行
				manager->scene = new Title::Object(manager);
				delete this;
			}
		}
	}
	void Object::Render()
	{
		DrawExtendGraph(280 + zoom, 80 + zoom,380+zoom,210+zoom ,graphic[0], TRUE);

		DrawExtendGraph(380 + zoom2, 80 + zoom2,480+zoom2,210+zoom2, graphic[1], TRUE);

		DrawExtendGraph(480 + zoom3, 80 + zoom3, 580 + zoom3, 210 + zoom3, graphic[2], TRUE);
	}
	
}