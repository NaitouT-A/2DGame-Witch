//���@�w�i�v���C���[�U���p�j�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;

namespace TutorialCircle {
	const  string  defGroupName = "���K���@�w";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		//�摜�f�[�^�i�[
		int graphic;
		int alivetime;
		int invoke;
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		bool isdead;
		bool isHit;
		bool create;
		//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
		Object(CManager*);
		//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
		~Object();
		//�������i�����groupName�̑���̂݁j
		bool  Initialize();
		//�j���\��
		void Dead();
		//�j��
		void Finalize();
		//�`��̍X�V
		void Render();
		//�X�V
		void Update();

		bool isDead();

		static Object::SP Create(CManager* pManager);
	};
}