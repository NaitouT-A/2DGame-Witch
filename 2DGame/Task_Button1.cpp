#pragma once
#include "Task_Button1.h"

namespace Button1
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		graphic = LoadGraph("./data/image/BookCoverSS.png");
		this->pos.x = 0;
		this->pos.y = 0;
		this->hitbox = MyGE::Box2D(0,0,100,600);
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
	}
	void Object::Update()
	{
			
	}
	void Object::Render()
	{
		DrawGraph(this->pos.x,this->pos.y,graphic,TRUE);
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return nullptr;
	}
}