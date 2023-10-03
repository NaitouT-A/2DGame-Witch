//�Q�[���̔w�i�i���Ɂj�I�u�W�F�N�g
#pragma once
#include "Task_GameBG.h"
namespace GameBG {
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜�f�[�^�i�[
		graphic = LoadGraph("./data/image/haikei5.png");
	}
	Object::~Object()
	{
	}
	void Object::Update()
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

	void Object::Render()
	{
		//�ǂ݂��񂾃O���t�B�b�N����]�`��
		DrawExtendGraph(0, 0, 1980, 1080, graphic, TRUE);
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob=Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return nullptr;
	}
}