#pragma once
#include "BChara.h"
class CManager;
namespace Button1
{
	const  string  defGroupName = "�{�^���P";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;

		//�摜
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
		//�`��̍X�V
		void Render();
		//�X�V
		void Update();
		//�j���\��
		void Dead();

		static Object::SP Create(CManager* pManager);
	};
}