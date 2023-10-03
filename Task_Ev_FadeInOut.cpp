//イベント管理（フェードイン・アウト）オブジェクト
#pragma once
#include "Task_Ev_FadeInOut.h"

namespace Ev_FadeInOut
{
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//ポジション
		this->pos = VGet(0, 0, 0);
		//カウント
		this->cnt = 0;
		//最初は停止させる
		this->Stop();
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
	void  Object::Update()
	{	
		if (this->mode == Mode::Out)
		{
			this->cnt+=2;
			if (this->cnt >255)
			{
				//イベントエンジンを再開させる
				ge->StopAll_G("イベント実行", false);
				//停止状態にする
				this->Dead();
			}
		}
		else if (this->mode == Mode::In)
		{
			this->cnt -= 2;
			if (this->cnt < 0)
			{
				//イベントエンジンを再開させる
				ge->StopAll_G("イベント実行", false);
				//停止状態にする
				this->Dead();
			}
		}
		else if (this->mode == Mode::Non)
		{
			//イベントエンジンを再開させる
			ge->StopAll_G("イベント実行", false);
			//停止状態にする
			this->Dead();
		}
	}

	void  Object::Render()
	{
		if (this->mode!=Mode::Non)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->cnt);
			DrawExtendGraph(0, 0, ge->Resolution.x, ge->Resolution.y, img, FALSE);
		}
	}

	void Object::CreateOrFadeIn(stringstream& ss_ ,CManager* pManager)
	{
		//新規作成か更新の判別
		auto p = ge->FindOne<Ev_FadeInOut::Object>("フェードIO");

		//新規作成の場合
		if (nullptr==p)
		{
			p = Object::Create(pManager);
			p->Set(ss_);
		}
		//更新の場合（基本はフェードアウト）
		else
		{
			p->Set(ss_);
		}
	}
	//フェードアウト・フェードインの準備を行う
	void Object::Set(stringstream& ss_)
	{
		//パラメータを分解する
		string filePath;
		ss_ >> filePath;
		//フェードインする場合	
		if (filePath=="in")
		{
			this->mode = Mode::In;
			this->cnt = 255;
		}
		else if (filePath == "out")
		{
			this->mode = Mode::Out;
			this->cnt = 0;
			//画像を読み込む 
			this->img = LoadGraph(filePath.c_str());
		}
		else if (filePath == "non")
		{
			this->mode = Mode::Non;
			this->cnt = 0;
		}
		//イベントエンジンを一時停止させる
		ge->StopAll_G("イベント実行",true);
		//停止状態を解除する
		this->Stop(false);
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}