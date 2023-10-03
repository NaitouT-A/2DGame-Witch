//
#pragma once
#include "Task_該当する名前.h"

namespace 該当する名前
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
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

	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}