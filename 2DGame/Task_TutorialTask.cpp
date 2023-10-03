//�`���[�g���A���̃~�b�V�����^�X�N
#pragma once
#include "Task_TutorialTask.h"
namespace TutorialTask
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		img = LoadGraph("./data/image/StageSelect.png");
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
	
	}
	void Object::Render()
	{
		DrawGraph(1300,240,img,TRUE);
		if (ge->tutorialKey<9)
		{
			SetFontSize(32);
			DrawFormatString(1920 - (18 * 32), 400, GetColor(255, 0, 0), "�D���ȕ�����");
			DrawFormatString(1920 - (16* 32), 432, GetColor(255, 0, 0), "�ړ����悤");
			SetFontSize(64);
			DrawFormatString(1920-(4*64), 400, GetColor(255, 0, 0), "%d/6��",ge->tutorialKey-2);
		}
		if (ge->tutorialKey >= 9&& ge->tutorialKey < 15)
		{
			SetFontSize(32);
			DrawFormatString(1920 - (18 * 32), 400, GetColor(255, 0, 0), "�G�̍U����");
			DrawFormatString(1920 - (16 * 32), 432, GetColor(255, 0, 0), "������悤");
			SetFontSize(64);
			DrawFormatString(1920 - (4 * 64),400, GetColor(255, 0, 0), "%d/5��", ge->tutorialKey - 9);
		}
		if (ge->tutorialKey >= 15 && ge->tutorialKey < 18)
		{
			SetFontSize(32);
			DrawFormatString(1920 - (17 * 32), 400, GetColor(255, 0, 0), "�G�ɍU����");
			DrawFormatString(1920 - (18 * 32), 432, GetColor(255, 0, 0), "���������悤");
			SetFontSize(64);
			DrawFormatString(1920 - (4 * 64), 400, GetColor(255, 0, 0), "%d/3��", ge->tutorialKey - 15);
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