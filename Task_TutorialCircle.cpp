//魔法陣（チュートリアルプレイヤー攻撃用）オブジェクト
#pragma once
#include "Task_TutorialCircle.h"
#include "Task_TutorialPlayer.h"
#include "Task_TutorialEnemy.h"
namespace TutorialCircle 
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像
		graphic = LoadGraph("./data/image/CircleS.png");
		//ポジション
		this->pos.x = 0;
		this->pos.y = 0;
		//生存時間
		this->alivetime = 0;
		this->invoke = 0;
		//生存フラグ
		this->isdead = false;
		//当たり判定
		this->hitbox = MyGE::Box2D(0,0,150,150);
		//ヒットしたか否か
		this->isHit = false;
		//生成されているか否か
		this->create = false;

		auto targets = ge->Find<TutorialPlayer::Object>("チュートリアルプレイヤ");
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
		//プレイヤーの攻撃判定をオフに
		auto player = ge->Find<TutorialPlayer::Object>("チュートリアルプレイヤ");
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
		auto player = ge->Find<TutorialPlayer::Object>("チュートリアルプレイヤ");
		auto it1 = player->begin()
			;
		MyGE::Box2D me = this->hitbox.OffsetCopy(this->pos);

		auto targets2 = ge->Find<TutorialEnemy::Object>("練習敵");
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