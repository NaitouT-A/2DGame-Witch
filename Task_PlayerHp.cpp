//�v���C���[��HP�̕\���p�I�u�W�F�N�g
#pragma once
#include "Task_PlayerHp.h"
namespace PlayerHp
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		graphic = LoadGraph("./data/image/Heart.png");
		//�|�W�V����
		this->pos.x = 0;
		this->pos.y = 0;
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