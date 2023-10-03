//�G�t�F�N�g�i�����j�I�u�W�F�N�g
#pragma once
#include "Task_EffectBomb.h"
namespace EffectBomb
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		LoadDivGraph("./data/image/Effect/explode.png", 15, 15, 1,96, 96, graphic);
		//�|�W�V����
		this->pos.x = 0;
		this->pos.y = 0;
		//���ʉ�
		this->sound = LoadSoundMem("./data/sound/SE_Bomb.mp3");
		//�Đ�
		ge->PlayMusicBack(sound,70);
	}
	Object::~Object()
	{
		DeleteSoundMem(sound);
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
		this->AnimTime++;
		if (this->AnimTime>2)
		{
			this->AnimTime = 0;
			this->AnimNum++;
			if (this->AnimNum>14)
			{
				this->AnimNum = 14;
				this->Dead();
			}
		}
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x+30, this->pos.y+30, this->pos.x+272, this->pos.y + 272, graphic[AnimNum], TRUE);
	}
	void Object::Setter(VECTOR pos_)
	{
		this->pos.x = pos_.x;
		this->pos.y = pos_.y;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}