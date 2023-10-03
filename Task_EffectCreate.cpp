//エフェクト生成用オブジェクト
#pragma once
#include "Task_EffectCreate.h"
namespace EffectCreate
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
	void Object::CreateEffect(Object::EFFECTTYPE type,VECTOR p)
	{
		EffectBomb::Object::SP eb;
		switch (type)
		{
		case BOMB:
			eb =EffectBomb::Object::Create(manager);
			eb->Setter(p);
			break;
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