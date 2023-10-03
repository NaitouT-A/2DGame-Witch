#pragma once
#include "Task_GameIntro.h"
namespace GameIntro {
	void Object::Update()
	{
		cnt++;
		if (cnt > 60)
			cnt = 0;
		GetMousePoint(&mx, &my);
		mouse = GetMouseInput();
		if (mx > 1500 && mx + 2 < 1900 && my > 800 && my + 2 < 1200)
		{
			if (mouse & MOUSE_INPUT_LEFT)
			{
				//ゲームにシーン移行
				if (ge->gamestage == MyGE::MyGameEngine::GameStage::stage1)
				{
					manager->scene = new Game::Object(manager);
					delete this;
				}
				//ゲームにシーン移行
				if (ge->gamestage == MyGE::MyGameEngine::GameStage::stage2)
				{
					manager->scene = new Game2::Object(manager);
					delete this;
				}

			}
		}
	}
	void Object::Render()
	{
		//読みこんだグラフィックを回転描画
		DrawExtendGraph(0, 0, 1980, 1080, graphic[0], TRUE);
		DrawBox(1500,800,1900,1200,GetColor(255,0,0),FALSE);

		if (cnt<30)
		{
			//読みこんだグラフィックを回転描画
			DrawExtendGraph(1500, 800, 1500+400, 800+300, graphic[1], TRUE);
		}
	}
}