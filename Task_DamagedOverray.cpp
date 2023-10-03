//ダメージ時のエフェクト（赤いヒット判定）オブジェクト
#pragma once
#include "Task_DamagedOverray.h"

namespace DamagedOverray
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像
		graphic = LoadGraph("./data/image/Damage.bmp");
		//ポジション
		this->pos.x = 0;
		this->pos.y = 0;
		//行動カウント
		this->moveCnt = 0;
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
		//削除待ちにする
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		this->moveCnt++;
		if (this->moveCnt/60>0.01f)
		{
			this->Dead();
		}
	}
	void Object::Render()
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(this->pos.x, this->pos.y, graphic, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return nullptr;
	}
}