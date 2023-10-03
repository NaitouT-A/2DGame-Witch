//�G�t�F�N�g�����p�I�u�W�F�N�g
#pragma once
#include "BChara.h"
#include "Task_EffectBomb.h"
class CManager;
namespace EffectCreate {
	const  string  defGroupName = "�G�t�F�N�g����";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		bool create;
		//�摜�f�[�^�i�[
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

		//�������i�����groupName�̑���̂݁j
		bool  Initialize();
		//�j���\��
		void Dead();

		static Object::SP Create(CManager* pManager);

		enum EFFECTTYPE {
			BOMB,
			Magic
		};
		void CreateEffect(Object::EFFECTTYPE type, VECTOR p);
		//���L����ϐ�******************
		bool isdead;
	};
}