//�C�x���g�Ǘ��i�t�F�[�h�C���E�A�E�g�j�I�u�W�F�N�g
#pragma once
#include "BChara.h"
class CManager;
namespace Ev_FadeInOut
{
	const  string  defGroupName = "�t�F�[�hIO";	//�O���[�v��
	class Object :public BTask
	{
		CManager* manager;

		int img;
		VECTOR pos;
		enum class Mode { Out, In,Non };
		Mode mode;
		int cnt;
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

		static void CreateOrFadeIn(stringstream& ss_, CManager* pManager);

		void Set(stringstream& ss_);

		static Object::SP Create(CManager* pManager);
	};
}