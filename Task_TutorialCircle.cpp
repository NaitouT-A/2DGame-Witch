//���@�w�i�`���[�g���A���v���C���[�U���p�j�I�u�W�F�N�g
#pragma once
#include "Task_TutorialCircle.h"
#include "Task_TutorialPlayer.h"
#include "Task_TutorialEnemy.h"
namespace TutorialCircle 
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		graphic = LoadGraph("./data/image/CircleS.png");
		//�|�W�V����
		this->pos.x = 0;
		this->pos.y = 0;
		//��������
		this->alivetime = 0;
		this->invoke = 0;
		//�����t���O
		this->isdead = false;
		//�����蔻��
		this->hitbox = MyGE::Box2D(0,0,150,150);
		//�q�b�g�������ۂ�
		this->isHit = false;
		//��������Ă��邩�ۂ�
		this->create = false;

		auto targets = ge->Find<TutorialPlayer::Object>("�`���[�g���A���v���C��");
		auto it = targets->begin();
		this->pos.x = (*it)->pos.x + 120;
		this->pos.y = (*it)->pos.y + 50;
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
		//�v���C���[�̍U��������I�t��
		auto player = ge->Find<TutorialPlayer::Object>("�`���[�g���A���v���C��");
		auto it = player->begin();
		(*it)->SetAttack(false);
		//�폜�҂��ɂ���
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		alivetime++;
		if (alivetime/60>lifeTime)
		{
			alivetime = 0;
			this->isdead = true;	
			this->Dead();
		}	
		auto player = ge->Find<TutorialPlayer::Object>("�`���[�g���A���v���C��");
		auto it1 = player->begin()
			;
		MyGE::Box2D me = this->hitbox.OffsetCopy(this->pos);

		auto targets2 = ge->Find<TutorialEnemy::Object>("���K�G");
		auto it2 = targets2->begin();
		MyGE::Box2D you2 = (*it2)->hitbox.OffsetCopy((*it2)->pos);

		if (you2.Hit(me))
		{
			if ((*it2)->motion != Motion::Hit)
				(*it2)->SetDamage((*it1)->getATK());
		}
		else
		{
			this->isHit = false;
		}

		if (this->isHit==true)
		{
			this->invoke++;
			if (this->invoke>1)
			{
				this->invoke = 0;
				this->Dead();
			}
		}
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x, this->pos.y, this->pos.x + 150, this->pos.y + 150, graphic, TRUE);
	}
	bool Object::isDead()
	{
		return this->isdead;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}