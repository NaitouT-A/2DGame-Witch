//�G�̍U������p�I�u�W�F�N�g
#pragma once
#include "Task_EAttack.h"
namespace EAttack
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�����蔻��
		this->hitbox = MyGE::Box2D(0,0,100,100);
		//�|�W�V����
		this->pos.x = 0;
		this->pos.y = 0;
		//�����t���O
		this->isdead = false;
		//�s���J�E���g
		this->moveCnt = 0;
	}
	Object::~Object()
	{
		this->isdead = true;
	}
	bool  Object::Initialize()
	{
		//�X�[�p�[�N���X������
		__super::Initialize(defGroupName);
		return true;
	}
	void Object::Dead()
	{
		//�폜�҂��ɂ���
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		this->moveCnt++;
		if (this->moveCnt/60>0.3)
		{
			this->Dead();
		}
	}
	void Object::Setter(VECTOR vec_)
	{
		this->pos.x = vec_.x+50;
		this->pos.y = vec_.y+50;
	}
	VECTOR Object::pGetter()
	{
		return this->pos;
	}
	MyGE::Box2D Object::Getter()
	{
		return this->hitbox;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}