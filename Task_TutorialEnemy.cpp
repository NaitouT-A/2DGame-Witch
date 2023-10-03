//�G�i�`���[�g���A���j�I�u�W�F�N�g
#pragma once
#include "Task_TutorialEnemy.h"
#include "string"
namespace TutorialEnemy 
{
	Object::Object(CManager* pManager)
	{
		//CManager�̃A�h���X�i�[
		manager = pManager;
		//�摜
		graphic=LoadGraph("./data/image/Training.png");
		//�|�W�V����
		DeafultPos = VGet(850, 0, 0);
		this->Setter(DeafultPos);
		//�����蔻��
		this->hitbox = MyGE::Box2D(0,0,150,150);
		//�s���J�E���^
		this->moveCnt = 0;
		//���[�V����
		this->motion = Motion::Stand;
		//HP
		this->Hp = 5;
		//�_���[�W
		this->damage = 0;
		//�s���L�[
		this->AttackKey = 0;
		//�G�t�F�N�g����
		auto ec = EffectCreate::Object::Create(manager);
	}
	Object::~Object()
	{
	}
	bool  Object::Initialize()
	{
		//�X�[�p�[�N���X������
		__super::Initialize(defGroupName);
		return true;
	}
	void Object::Dead()
	{
		//�폜�҂��ɂ���
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		this->moveCnt++;
		if (ge->tutorialKey>=9&&ge->tutorialKey<19)
		{
			Think();
			Move();
		}
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x, this->pos.y, this->pos.x + 150, this->pos.y + 150, graphic, TRUE);

		if (this->motion!=Motion::Stand&& this->motion != Motion::Hit && this->motion != Motion::Dead && this->moveCnt> 45&& this->moveCnt> 45)
		{
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					if (AttackPos[y][x]==1&&this->motion==Motion::BeforeAttack)
					{
						SetFontSize(128);
						DrawFormatString(board[y][x].x + 80, board[y][x].y + 80,
						GetColor(255, 255-this->moveCnt*2, 255 - this->moveCnt*2), "!");
						SetFontSize(64);
					}
				}
			}
		}
	}
	void Object::SetDamage(int damage_)
	{
		this->damage = damage_;
		this->Hp -= damage;
		auto ehp = ge->Find<EnemyHp::Object>("�G�l�~�[HP");
		for (auto it = ehp->begin(); it != ehp->end(); it++)
		{
			if (it == (ehp->end() - 1))
			{
				(*it)->Dead();
				break;
			}
		}
		this->motion = Motion::Hit;
		if (ge->tutorialKey >= 14 && ge->tutorialKey < 18) {
			ge->tutorialKey += 1;
			if (ge->tutorialKey > 18) { ge->tutorialKey = 18; }
		}
		if (this->Hp<=0)
		{
			this->Hp = 0;
		}
	}
	void Object::SetBoardPos(VECTOR vec_[3][3])
	{
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				this->board[y][x] = vec_[y][x];
			}
		}
	}
	void Object::Setter(VECTOR vec_)
	{
		this->pos.x = vec_.x+50;
		this->pos.y = vec_.y+50;
	}
	void Object::Think()
	{
		BChara::Motion nm = this->motion;
		switch (nm)
		{
		case Motion::Stand:
			if (this->moveCnt / 60 > 1.0f) { nm = Motion::BeforeAttack; this->moveCnt = 0; }
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0;}
			break;
		case Motion::BeforeAttack:
			switch (AttackKey)
			{
			case 0:
				AttackLoad("./data/attack/stage1/CenterAttack.txt");
				if (this->moveCnt / 60 > 1.2f){nm = Motion::Attack;this->moveCnt = 0;}

			break;
			}
			break;
		case Motion::Attack:
			if (this->moveCnt / 60 > 0.5f) { nm = Motion::Stand; AttackKey = 0; this->moveCnt = 0;  }
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0; }
			break;
		case Motion::Hit:
			if (this->moveCnt / 60 > 0.2f) 
			{ 
				nm = Motion::Stand; 
				this->moveCnt = 0; 
			}
			break;
		case Motion::Dead:
			Setter(DeafultPos);
			auto targets = ge->Find<EffectCreate::Object>("�G�t�F�N�g����");
			auto it = targets->begin();
			(*it)->CreateEffect((*it)->BOMB, this->pos);	
			break;
		}
		this->updateMotion(nm);
	}
	void Object::Move()
	{
		switch (this->motion)
		{
		case Motion::Stand:
			Setter(DeafultPos);
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					this->AttackPos[y][x] = 0;

					this->create[y][x] = false;
				}
			}
			break;
		case Motion::BeforeAttack:
			break;
		case Motion::Attack:
			Setter(board[1][1]);
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					if (this->create[y][x] == false)
					{
						if (this->AttackPos[y][x] == 1)
						{
							auto targets = ge->Find<EffectCreate::Object>("�G�t�F�N�g����");
							auto it = targets->begin();
							(*it)->CreateEffect((*it)->BOMB, board[y][x]);

							auto ea = EAttack::Object::Create(manager);
							ea->Setter(board[y][x]);

							this->create[y][x] = true;
						}
					}
				}
			}
			break;
		case Motion::Hit:
			break;
		case Motion::Dead:
			break;
		}
	}
	bool Object::AttackLoad(const string& fpath_)
	{
		ifstream fin(fpath_);
		if (!fin) { return false; }

		for (int y=0;y<3;++y)
		{
			for (int x=0;x<3;++x)
			{
				fin >> AttackPos[y][x];
			}
		}
		fin.close();

		return true;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}