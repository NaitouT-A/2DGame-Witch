//ゲームオーバーシーン
#pragma once
#include "Task_GameOver.h"
namespace GameOver
{
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		
		//画像データ格納
		LoadDivGraph("./data/image/PlayerX.png", 70, 10, 7, Player_ImageX / 10, Player_ImageY / 7, graphic);
		img[0] = LoadGraph("./data/image/GameOver.png");
		img[1] = LoadGraph("./data/image/Overlogo.png");
		img[2] = LoadGraph("./data/image/GameResult.png");
		//アニメーションの初期値
		anim = 50;
		//アニメカウンタ
		anicnt = 0;
		//再生
		ge->PlayMusicBack(music, 70);
	};
	void Object::Update()
	{
		anicnt++;
		Anim();
		if (manager->GetKey()[KEY_INPUT_RETURN] > 0)
		{
			ge->gamestate = MyGE::MyGameEngine::GameState::Non;
			//ゲームにシーン移行
			manager->scene = new Title::Object(manager);
			delete this;
		}
		if (anicnt>7)
		{
			anim++;
			anicnt = 0;
		}
		if (anim>62)
		{
			anim = 62;
		}
	}
	void Object::Render()
	{
		DrawGraph(0, 0, img[0], FALSE);

		DrawGraph(600, 100+y, img[1], TRUE);

		DrawGraph(650, 300, img[2], TRUE);

		DrawExtendGraph(600, 300, 600 + 897, 300 + 672, graphic[anim], TRUE);
	}
	void Object::Anim()
	{
		y += 1 + yvec;
		if (ypos == false)
		{
			yvec += 0.02;
		}
		else
		{
			yvec -= 0.02;
		}

		if (yvec < -2.2)
		{
			ypos = false;
		}
		if (yvec > 0.2)
		{
			ypos = true;
		}
	}
}