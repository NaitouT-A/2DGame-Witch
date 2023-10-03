//�_���[�W���̃G�t�F�N�g�i�Ԃ��q�b�g����j�I�u�W�F�N�g
#pragma once
#include "Task_DamagedOverray.h"

namespace DamagedOverray
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		graphic = LoadGraph("./data/image/Damage.bmp");
		//�|�W�V����
		this->pos.x = 0;
		this->pos.y = 0;
		//�s���J�E���g
		this->moveCnt = 0;
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
		//�폜�҂��ɂ���
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		this->moveCnt++;
		if (this->moveCnt/60>0.01f)
		{
			this->Dead();
		}
	}
	void Object::Render()
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(this->pos.x, this->pos.y, graphic, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return nullptr;
	}
}