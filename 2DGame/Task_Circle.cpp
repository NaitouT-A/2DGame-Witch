//魔法陣（プレイヤー攻撃用）オブジェクト
#pragma once
#include "Task_Circle.h"
#include "Task_Player.h"
#include "Task_Enemy.h"
#include "Task_Enemy2.h"
namespace Circle 
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		graphic = LoadGraph("./data/image/CircleS.png");
		this->pos.x = 0;
		this->pos.y = 0;
		this->alivetime = 0;
		this->invoke = 0;
		this->isdead = false;
		this->hitbox = MyGE::Box2D(0,0,150,150);
		this->isHit = false;
		this->create = false;

		auto targets = ge->Find<Player::Object>("プレイヤ");
		auto it = targets->begin();
		this->pos.x = (*it)->pos.x + 120;
		this->pos.y = (*it)->pos.y + 50;
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
		//プレイヤの攻撃状態を解除
		auto player = ge->Find<Player::Object>("プレイヤ");
		auto it = player->begin();
		(*it)->SetAttack(false);
		//削除待ちにする
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		alivetime++;
		if (alivetime/60>lifeTime)
		{
			alivetime = 0;
			this->isdead = true;	
			this->Dead();
		}	

		auto player = ge->Find<Player::Object>("プレイヤ");
		auto it1 = player->begin()
			;
		MyGE::Box2D me = this->hitbox.OffsetCopy(this->pos);

		//ステージによって当たる敵を変える
		if (ge->gamestage == MyGE::MyGameEngine::GameStage::stage1)
		{
			auto targets2 = ge->Find<Enemy2::Object>("敵2");
			auto it2 = targets2->begin();
			MyGE::Box2D you2 = (*it2)->hitbox.OffsetCopy((*it2)->pos);

			if (you2.Hit(me))
			{
				if ((*it2)->motion != Motion::Hit)
					(*it2)->SetDamage((*it1)->getATK());
			}
			else
			{
				this->isHit = false;
			}
		}

		if (ge->gamestage == MyGE::MyGameEngine::GameStage::stage2)
		{
			auto targets = ge->Find<Enemy::Object>("敵");
			auto it = targets->begin();
			MyGE::Box2D you = (*it)->hitbox.OffsetCopy((*it)->pos);

			if (you.Hit(me))
			{
				if ((*it)->motion != Motion::Hit)
					(*it)->SetDamage((*it1)->getATK());
			}
			else
			{
				this->isHit = false;
			}
		}

		//命中したならば
		if (this->isHit==true)
		{
			this->invoke++;
			if (this->invoke>1)
			{
				this->invoke = 0;
				this->Dead();
			}
		}
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x, this->pos.y, this->pos.x + 150, this->pos.y + 150, graphic, TRUE);
	}
	bool Object::isDead()
	{
		return this->isdead;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}