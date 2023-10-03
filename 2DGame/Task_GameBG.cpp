//ゲームの背景（書庫）オブジェクト
#pragma once
#include "Task_GameBG.h"
namespace GameBG {
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像データ格納
		graphic = LoadGraph("./data/image/haikei5.png");
	}
	Object::~Object()
	{
	}
	void Object::Update()
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
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}

	void Object::Render()
	{
		//読みこんだグラフィックを回転描画
		DrawExtendGraph(0, 0, 1980, 1080, graphic, TRUE);
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob=Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return nullptr;
	}
}