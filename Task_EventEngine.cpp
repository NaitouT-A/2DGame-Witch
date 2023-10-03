//イベント管理用オブジェクト
#pragma once
#include "Task_EventEngine.h"
#include "Task_Ev_Message.h"
#include "Task_Ev_Image.h"
#include "Task_Ev_FadeInOut.h"
#include "Task_GameOver.h"
namespace EventEngine
{
	Object::WP Object::instance;
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;

		//イベント中に動かないようにする
		ge->StopAll_G("プレイヤ",true);
		ge->StopAll_G("チュートリアルプレイヤ", true);
		ge->StopAll_G("敵2", true);
		ge->StopAll_G("敵", true);
		ge->StopAll_G("練習敵", true);
		ge->StopAll_G("魔法陣", true);
		ge->StopAll_G("ゲーム盤", true);
		ge->StopAll_G("ダメージUI", true);
		ge->StopAll_G("攻撃範囲", true);

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
		//イベント終了時に動かす
		ge->StopAll_G("プレイヤ", false);
		ge->StopAll_G("チュートリアルプレイヤ", false);
		ge->StopAll_G("敵2", false);
		ge->StopAll_G("敵", false);
		ge->StopAll_G("練習敵", false);
		ge->StopAll_G("魔法陣", false);
		ge->StopAll_G("ゲーム盤", false);
		ge->StopAll_G("ダメージUI", false);
		ge->StopAll_G("攻撃範囲", false);
	}
	void Object::Update()
	{
		if (!this->evFile) { this->Dead(); }

		string lineText;
		string headerText;
		string dataText;
		while (this->ReadLine(lineText))
		{
			string::size_type t = lineText.find(">");
			headerText = lineText.substr(0, t);
			dataText = lineText.substr(t + 1);
			bool rtv = this->Execute(headerText,dataText);
			if (false == rtv||BTask::Taskstate::Normal!=this->taskstate)
			{
				break;
			}
		}
	}
	void Object::Render()
	{

	}

	Object::SP Object::Create_Mutex(CManager* pManager)
	{
		if (auto p=instance.lock())
		{
			return nullptr;
		}
		else
		{
			p = Object::Create(pManager);
			instance = p;
			return p;
		}
	}

	bool Object::Set(const string& fPath_)
	{
		if (this->evFile.is_open())
		{
			this->evFile.close();
		}

		this->evFile.open(fPath_);

		if (!this->evFile)
		{
			return false;
		}

		return true;
	}
	bool Object::ReadLine(string& lineT_)
	{
		bool rtv = false;
		while (getline(this->evFile,lineT_))
		{
			if (string::npos == lineT_.find_first_not_of("　")) { continue; }
			if ('/' == lineT_.at(0)) { continue; }
			if (string::npos == lineT_.find(">")) { continue; }
			rtv = true;
			break;
		}
		return rtv;
	}
	bool Object::Execute(string& hs_,string& ds_)
	{
		string::size_type t;
		while ((t=ds_.find_first_of("(,);"))!=string::npos)
		{
			ds_[t] = ' ';
		}
		stringstream ss;
		ss << ds_;

		if (hs_=="end")
		{
			this->Dead();
		}
		else if (hs_ == "msg") { Ev_Message::Object::CreateOrReset(ss,manager); }
		else if (hs_ == "evimg") { Ev_Image::Object::CreateOrReset(ss, manager); }
		else if (hs_ == "fade_io") { Ev_FadeInOut::Object::CreateOrFadeIn(ss, manager); }
		else
		{
			return false;
		}
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