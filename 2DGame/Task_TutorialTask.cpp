//チュートリアルのミッションタスク
#pragma once
#include "Task_TutorialTask.h"
namespace TutorialTask
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像
		img = LoadGraph("./data/image/StageSelect.png");
	}
	Object::~Object()
	{
	}
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName);
		return true;
	}
	void Object::Dead()
	{
		//削除待ちにする
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
	
	}
	void Object::Render()
	{
		DrawGraph(1300,240,img,TRUE);
		if (ge->tutorialKey<9)
		{
			SetFontSize(32);
			DrawFormatString(1920 - (18 * 32), 400, GetColor(255, 0, 0), "好きな方向に");
			DrawFormatString(1920 - (16* 32), 432, GetColor(255, 0, 0), "移動しよう");
			SetFontSize(64);
			DrawFormatString(1920-(4*64), 400, GetColor(255, 0, 0), "%d/6回",ge->tutorialKey-2);
		}
		if (ge->tutorialKey >= 9&& ge->tutorialKey < 15)
		{
			SetFontSize(32);
			DrawFormatString(1920 - (18 * 32), 400, GetColor(255, 0, 0), "敵の攻撃を");
			DrawFormatString(1920 - (16 * 32), 432, GetColor(255, 0, 0), "回避しよう");
			SetFontSize(64);
			DrawFormatString(1920 - (4 * 64),400, GetColor(255, 0, 0), "%d/5回", ge->tutorialKey - 9);
		}
		if (ge->tutorialKey >= 15 && ge->tutorialKey < 18)
		{
			SetFontSize(32);
			DrawFormatString(1920 - (17 * 32), 400, GetColor(255, 0, 0), "敵に攻撃を");
			DrawFormatString(1920 - (18 * 32), 432, GetColor(255, 0, 0), "命中させよう");
			SetFontSize(64);
			DrawFormatString(1920 - (4 * 64), 400, GetColor(255, 0, 0), "%d/3回", ge->tutorialKey - 15);
		}
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}