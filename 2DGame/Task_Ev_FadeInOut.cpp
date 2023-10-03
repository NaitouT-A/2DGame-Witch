//�C�x���g�Ǘ��i�t�F�[�h�C���E�A�E�g�j�I�u�W�F�N�g
#pragma once
#include "Task_Ev_FadeInOut.h"

namespace Ev_FadeInOut
{
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�|�W�V����
		this->pos = VGet(0, 0, 0);
		//�J�E���g
		this->cnt = 0;
		//�ŏ��͒�~������
		this->Stop();
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
	void  Object::Update()
	{	
		if (this->mode == Mode::Out)
		{
			this->cnt+=2;
			if (this->cnt >255)
			{
				//�C�x���g�G���W�����ĊJ������
				ge->StopAll_G("�C�x���g���s", false);
				//��~��Ԃɂ���
				this->Dead();
			}
		}
		else if (this->mode == Mode::In)
		{
			this->cnt -= 2;
			if (this->cnt < 0)
			{
				//�C�x���g�G���W�����ĊJ������
				ge->StopAll_G("�C�x���g���s", false);
				//��~��Ԃɂ���
				this->Dead();
			}
		}
		else if (this->mode == Mode::Non)
		{
			//�C�x���g�G���W�����ĊJ������
			ge->StopAll_G("�C�x���g���s", false);
			//��~��Ԃɂ���
			this->Dead();
		}
	}

	void  Object::Render()
	{
		if (this->mode!=Mode::Non)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->cnt);
			DrawExtendGraph(0, 0, ge->Resolution.x, ge->Resolution.y, img, FALSE);
		}
	}

	void Object::CreateOrFadeIn(stringstream& ss_ ,CManager* pManager)
	{
		//�V�K�쐬���X�V�̔���
		auto p = ge->FindOne<Ev_FadeInOut::Object>("�t�F�[�hIO");

		//�V�K�쐬�̏ꍇ
		if (nullptr==p)
		{
			p = Object::Create(pManager);
			p->Set(ss_);
		}
		//�X�V�̏ꍇ�i��{�̓t�F�[�h�A�E�g�j
		else
		{
			p->Set(ss_);
		}
	}
	//�t�F�[�h�A�E�g�E�t�F�[�h�C���̏������s��
	void Object::Set(stringstream& ss_)
	{
		//�p�����[�^�𕪉�����
		string filePath;
		ss_ >> filePath;
		//�t�F�[�h�C������ꍇ	
		if (filePath=="in")
		{
			this->mode = Mode::In;
			this->cnt = 255;
		}
		else if (filePath == "out")
		{
			this->mode = Mode::Out;
			this->cnt = 0;
			//�摜��ǂݍ��� 
			this->img = LoadGraph(filePath.c_str());
		}
		else if (filePath == "non")
		{
			this->mode = Mode::Non;
			this->cnt = 0;
		}
		//�C�x���g�G���W�����ꎞ��~������
		ge->StopAll_G("�C�x���g���s",true);
		//��~��Ԃ���������
		this->Stop(false);
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}