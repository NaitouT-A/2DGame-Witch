//�L�����N�^�N���X
#pragma once
#include "Dxmain.h"
#include "Dxlib.h"
#include"SceneMgr.h"
#include "MyGE.h"
class BChara:public BTask
{
public:
	using SP = shared_ptr<BChara>;
	using WP = weak_ptr<BChara>;
	//**********************************************************************************
	VECTOR pos;//�|�W�V����
	int AnimTime;//�A�j���[�V��������
	int AnimNum;//�A�j���[�V�����ԍ�
	float moveCnt;//�s���J�E���^
	enum class Motion//���[�V����
	{
		unnon,
		Stand,
		BeforeAttack,
		Attack,
		Attack2,
		Attack3,
		Attack4,
		Hit,
		Dead,
	};
	Motion motion;

	bool updateMotion(Motion nm_);//���[�V�����X�V
	MyGE::Box2D hitbox;//�����蔻��
	BChara(): BTask(manager)
	{
			pos = VGet(0, 0, 0),
			motion = Motion::unnon,
			AnimTime = 0,
			AnimNum = 0,
			hitbox = MyGE::Box2D(0, 0, 0, 0),
			moveCnt = 0;
	}

};