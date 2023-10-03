//�`���[�g���A���̃~�b�V�����^�X�N
#pragma once
#include "BChara.h"
class CManager;
namespace TutorialTask
{
	const  string  defGroupName = "�~�b�V����";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;

		int img;
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
		Object(CManager*);
		//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
		~Object();
		//�������i�����groupName�̑���̂݁j
		bool  Initialize();
		//�`��̍X�V
		void Render();
		//�X�V
		void Update();
		//�j���\��
		void Dead();

		static Object::SP Create(CManager* pManager);
	};
}