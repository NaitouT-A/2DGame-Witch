//�C�x���g�Ǘ��i�摜�\���p�j�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace Ev_Image
{
	const  string  defGroupName = "�C�x���g�摜";	//�O���[�v��
	class Object :public BTask
	{
		CManager* manager;

		int img;
		VECTOR pos;
		MyGE::Box2D drawBase;
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