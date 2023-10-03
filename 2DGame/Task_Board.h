//�Q�[���Ձi�}�X�P�ʁj�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace Board {
	const  string  defGroupName = "�Q�[����";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		//�摜�f�[�^�i�[
		int graphic;
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
		Object(CManager*);
		//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
		~Object();
		//�������i�����groupName�̑���̂݁j
		bool  Initialize();
		//�j���\��
		void Dead();
		//�`��̍X�V
		void Render();
		//�X�V
		void Update();

		VECTOR Getter();//���W�Q�b�^�[

		void Setter(VECTOR vec_);//���W�Z�b�^�[

		static Object::SP Create(CManager* pManager);
	};
}