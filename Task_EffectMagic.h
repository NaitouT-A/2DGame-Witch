//�G�t�F�N�g�i���@�j�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace EffectMagic {
	const  string  defGroupName = "�{��";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		//�摜�f�[�^�i�[
		int graphic[15];
		int sound;
		//*****************************
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
		Object(CManager*);
		//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
		~Object();
		//�`��̍X�V
		void Render();
		//�X�V
		void Update();

		void Setter(VECTOR pos_);

		//�������i�����groupName�̑���̂݁j
		bool  Initialize();
		//�j���\��
		void Dead();

		static Object::SP Create(CManager* pManager);
		//���L����ϐ�******************
	};
}