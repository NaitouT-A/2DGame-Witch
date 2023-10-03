//�C�x���g�Ǘ��p�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace EventEngine
{
	const  string  defGroupName = "�C�x���g���s";	//�O���[�v��
	class Object :public BTask
	{
		CManager* manager;

		ifstream evFile;	
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		static WP instance;
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

		static Object::SP Create_Mutex(CManager* pManager);

		bool Set(const string& fPath_);

		bool ReadLine(string& lineT_);

		bool Execute(string& hs_, string& ds_);

		static Object::SP Create(CManager* pManager);
	};
}