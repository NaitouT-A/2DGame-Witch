//�G�̍U������p�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace EAttack {
	const  string  defGroupName = "�U���͈�";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		//�摜�f�[�^�i�[
	public:
		bool isdead;
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
		Object(CManager*);
		//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
		~Object();
		//�������i�����groupName�̑���̂݁j
		bool  Initialize();

		void Update();
		//�j���\��
		void Dead();

		void Setter(VECTOR vec_);

		MyGE::Box2D Getter();

		VECTOR pGetter();

		static Object::SP Create(CManager* pManager);
	};
}