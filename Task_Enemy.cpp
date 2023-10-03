//敵（魔女）オブジェクト
#pragma once
#include "Task_Enemy.h"
namespace Enemy 
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像
		LoadDivGraph("./data/image/Enemy2.png", 50,10,5, 192, 193, graphic);
		//ポジション
		DeafultPos = VGet(850, 0, 0);
		this->pos = DeafultPos;
		//当たり判定
		this->hitbox = MyGE::Box2D(0,0,150,150);
		//行動カウント
		this->moveCnt = 0;
		//モーション
		this->motion = Motion::Stand;
		//HP
		this->Hp = 20;
		//ダメージ
		this->damage = 0;
		//行動キー
		this->AttackKey = 0;
		//エフェクト生成
		auto ec = EffectCreate::Object::Create(manager);
	}
	Object::~Object()
	{
	}
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName);
		return true;
	}
	void Object::Dead()
	{
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		this->moveCnt++;
		Think();
		Move();
		Object::ConutAnimTime();
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x, this->pos.y, this->pos.x + 150, this->pos.y + 150, graphic[this->AnimNum], TRUE);

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
		if (this->motion != Motion::Hit)
		{
			this->Hp -= damage;
			auto ehp = ge->Find<EnemyHp::Object>("エネミーHP");
			for (auto it = ehp->begin(); it != ehp->end(); it++)
			{
				if (it == (ehp->end() - 1))
				{
					(*it)->Dead();
					break;
				}
			}
		}
		this->motion = Motion::Hit;
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
	void Object::ConutAnimTime()
	{
		this->AnimTime++;
		if (this->AnimTime >= 49)
		{
			this->AnimTime = 0;
		}
		int animtable[] = { 0,1,0,1,0};
		this->AnimNum = animtable[this->AnimTime / 10];
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
				AttackLoad("./data/attack/stage2/SingleAttack.txt");
				if (this->moveCnt / 60 > 1.2f){nm = Motion::Attack;this->moveCnt = 0;}

			break;
			case 1:
				AttackLoad("./data/attack/stage2/SiegeAttack.txt");
				if (this->moveCnt / 60 > 1.2f) { nm = Motion::Attack2; this->moveCnt = 0; }

				break;
			case 2:
				AttackLoad("./data/attack/stage2/ReverseCross.txt");
				if (this->moveCnt / 60 > 1.2f) { nm = Motion::Attack3; this->moveCnt = 0; }

				break;
			case 3:
				AttackLoad("./data/attack/stage2/Cross.txt");
				if (this->moveCnt / 60 > 1.2f) { nm = Motion::Attack4; this->moveCnt = 0; }

				break;
			}

			break;
		case Motion::Attack:
			preattackkey = AttackKey;
			if (this->moveCnt / 60 > 0.3f) { nm = Motion::Stand; AttackKey = 1; this->moveCnt = 0; }
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0; }
			break;
		case Motion::Attack2:
			preattackkey = AttackKey;
			if (this->moveCnt / 60 > 0.3f) { nm = Motion::Stand; AttackKey = 2; this->moveCnt = 0; }
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0; }
			break;
		case Motion::Attack3:
			preattackkey = AttackKey;
			if (this->moveCnt / 60 > 0.3f) { nm = Motion::Stand; AttackKey = 3; this->moveCnt = 0; }
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0; }
			break;
		case Motion::Attack4:
			preattackkey = AttackKey;
			if (this->moveCnt / 60 > 0.5f) { nm = Motion::Stand; AttackKey = 0; this->moveCnt = 0; }
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0; }
			break;
		case Motion::Hit:
			preattackkey = AttackKey;
			if (this->moveCnt / 60 > 0.2f)
			{
				nm = Motion::Stand;

				if (AttackKey < 3)
				{
					AttackKey = preattackkey + 1;
					if (AttackKey > 3)
					{
						//AttackKey = 0;
						int i = 0;
					}
				}
				else
					AttackKey = 0;

				this->moveCnt = 0;
			}
			if (this->Hp <= 0) { nm = Motion::Dead; this->moveCnt = 0; }
			break;
		case Motion::Dead:
			Setter(DeafultPos);
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
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					if (this->create[y][x] == false)
					{
						if (this->AttackPos[y][x] == 1)
						{
							auto targets = ge->Find<EffectCreate::Object>("エフェクト生成");
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
		case Motion::Attack2:
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					if (this->create[y][x] == false)
					{
						if (this->AttackPos[y][x] == 1)
						{
							auto targets = ge->Find<EffectCreate::Object>("エフェクト生成");
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
		case Motion::Attack3:
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					if (this->create[y][x] == false)
					{
						if (this->AttackPos[y][x] == 1)
						{
							auto targets = ge->Find<EffectCreate::Object>("エフェクト生成");
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
		case Motion::Attack4:
			Setter(board[1][1]);
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					if (this->create[y][x] == false)
					{
						if (this->AttackPos[y][x] == 1)
						{
							auto targets = ge->Find<EffectCreate::Object>("エフェクト生成");
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
	int Object::Anim()
	{
		int imgNum = 0;
		switch (this->motion)
		{
		case Motion::Stand:
			imgNum = 0;
			break;
		case Motion::Attack:
			imgNum = 1;
			break;
		case Motion::Attack2:
			imgNum = 1;
			break;
		case Motion::Attack3:
			imgNum = 1;
			break;
		case Motion::Attack4:
			imgNum = 1;
			break;
		case Motion::Hit:
			imgNum = 2;
			break;
		case Motion::Dead:
			imgNum = 3;
			break;
		}
		return imgNum;
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