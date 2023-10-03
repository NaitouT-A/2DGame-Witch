//プレイヤーのHPの表示用オブジェクト
#pragma once
#include "Task_PlayerHp.h"
namespace PlayerHp
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像
		graphic = LoadGraph("./data/image/Heart.png");
		//ポジション
		this->pos.x = 0;
		this->pos.y = 0;
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
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x, this->pos.y,this->pos.x + 64,this->pos.y+64, graphic, TRUE);
	}
	void Object::Setter(VECTOR vec_)
	{
		this->pos = vec_;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}