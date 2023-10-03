//�v���C���[�p�I�u�W�F�N�g
#pragma once
#include "BChara.h"
#include "Task_Circle.h"
class CManager;
namespace Player
{
	const  string  defGroupName = "�v���C��";	//�O���[�v��
	class Object :public BChara
	{
		CManager* manager;
		//�摜�f�[�^�i�[
		int graphic[70];
		bool Keycheck;
		VECTOR board[3][3];
		bool isAttack;
		int  ATK;
		int HitCnt;
		int Hp;
		int sound[2];
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
		
		void Setter(VECTOR vec_);

		void SetBoardPos(VECTOR vec_[3][3]);

		void SetAttack(bool b);

		int getATK();

		void ConutAnimTime();

		void Think();

		void Move();

		static Object::SP Create(CManager* pManager);
		//���L����ϐ�*******************************
		bool isHit;
	};
}