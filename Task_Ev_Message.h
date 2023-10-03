//�C�x���g�Ǘ��i���b�Z�[�W�p�j�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace Ev_Message
{
	const  string  defGroupName = "���b�Z�[�W�\���g";	//�O���[�v��
	class Object :public BTask
	{
		CManager* manager;
		int img[1];
		int bgNumber;
		VECTOR pos;
		string msgText;
		int timeCnt;
		int timeLimit;
		int mx, my;
		int mouse;
		bool PutM;

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

		static void CreateOrReset(stringstream& ss_, CManager* pManager);

		void Set(const string& taskName_, stringstream& ss_);

		static Object::SP Create(CManager* pManager);
	};
}