//�G�i�X���C���j�I�u�W�F�N�g
#pragma once
#include "BChara.h"
#include "Task_EffectCreate.h"
#include "Task_EAttack.h"
#include "Task_EnemyHp.h"
class CManager;
namespace Enemy2 {
	const  string  defGroupName = "�G2";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		//�摜�f�[�^�i�[
		int graphic[4];
		//*********************
		int AnimTime;
		int AnimNum;
		int Hp;
		int damage;
		VECTOR DeafultPos;
		VECTOR board[3][3];
		int AttackPos[3][3];
		int AttackKey;
		bool create[3][3];
		int preattackkey = 0;
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

		void ConutAnimTime();

		void Think();

		void Move();

		void SetBoardPos(VECTOR vec_[3][3]);

		void Setter(VECTOR vec_);

		void SetDamage(int damage_);

		MyGE::Box2D Getter();

		int Anim();

		bool AttackLoad(const string& fpath_);

		static Object::SP Create(CManager* pManager);
	};
}