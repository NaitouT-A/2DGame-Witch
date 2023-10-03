//�C�x���g�Ǘ��i���b�Z�[�W�p�j�I�u�W�F�N�g
#pragma once
#include "Task_Ev_Message.h"

namespace Ev_Message
{
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		this->img[0]=LoadGraph("./data/image/Message.png");
		//�|�W�V����
		this->pos.x;
		this->pos.y = 580;
		//�e�L�X�g
		this->msgText = " ";
		//�w�i�ԍ�
		this->bgNumber = 0;
		//��~
		this->Stop();
		//�}�E�X��������Ă��邩�̃t���O
		this->PutM = false;
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
		GetMousePoint(&mx, &my);
		mouse = GetMouseInput();
		if ((this->timeLimit!=0&&this->timeCnt>=this->timeLimit)
			|| manager->GetKey()[KEY_INPUT_RETURN]!=0 && this->PutM == false)
		{
			this->Stop();
			ge->StopAll_G("�C�x���g���s",false);
			this->PutM = true;
		}
		else
		{
			this->timeCnt++;
		}
		if (manager->GetKey()[KEY_INPUT_RETURN]<= 0)
		{
			this->PutM = false;
		}
	}
	void Object::Render()
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawExtendGraph(this->pos.x,this->pos.y,this->pos.x+1920,this->pos.y+500,img[bgNumber],TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(this->pos.x+50,this->pos.y+64,GetColor(255,255,255),this->msgText.c_str());
	}
	void Object::Set(const string& taskName_, stringstream& ss_)
	{
		int timeL;
		string msg;
		ss_ >> timeL >> msg;
		if (msg=="off")
		{
			this->Dead();
			return;
		}

		this->timeCnt = 0;
		this->timeLimit = timeL;
		this->msgText = msg;

		string::size_type ast;
		while ((ast = msgText.find("*")) != string::npos)
		{
			msgText.at(ast) = '\n';
		}

		ge->StopAll_G("�C�x���g���s",true);

		this->Stop(false);
	}
	void Object::CreateOrReset(stringstream& ss_, CManager* pManager)
	{
		string taskName;
		ss_ >> taskName;
		auto p= ge->FindOne<Ev_Message::Object>("���b�Z�[�W�\���g");
		if (nullptr==p)
		{
			p = Object::Create(pManager);
			p->Set(taskName, ss_);
		}
		else
		{		
			p->Set(taskName,ss_);
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