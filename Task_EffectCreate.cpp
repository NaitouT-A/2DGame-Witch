//�G�t�F�N�g�����p�I�u�W�F�N�g
#pragma once
#include "Task_EffectCreate.h"
namespace EffectCreate
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
	}
	Object::~Object()
	{
	}
	bool  Object::Initialize()
	{
		//�X�[�p�[�N���X������
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