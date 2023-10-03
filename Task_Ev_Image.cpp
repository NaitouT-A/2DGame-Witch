//イベント管理（画像表示用）オブジェクト
#pragma once
#include "Task_Ev_Image.h"

namespace Ev_Image
{
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//ポジション
		this->pos = VGet(0,0,0);
		//描画サイズ
		this->drawBase=MyGE::Box2D(0, 0, 0, 0); 
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
	
	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x+drawBase.x, this->pos.y + drawBase.y,this->pos.x+this->drawBase.w,this->pos.y+this->drawBase.h,img,TRUE);
	}
	void Object::Set(const string& taskName_, stringstream& ss_)
	{
		string filePath;
		ss_ >> filePath;

		if (filePath=="off")
		{
			this->Dead();
			return;
		}
		this->name = taskName_;
		this->img = LoadGraph(filePath.c_str());


		enum class XPosition { Left, Center, Right };
		enum class YPosition { Up, Down };
		XPosition xPos = XPosition::Left;
		YPosition yPos = YPosition::Up;
		string posAndRev;
		ss_ >> posAndRev;
	
		if (string::npos != posAndRev.find("L")) { xPos = XPosition::Left; }
		if (string::npos != posAndRev.find("R")) { xPos = XPosition::Right; }
		if (string::npos != posAndRev.find("C")) { xPos = XPosition::Center; }

		if (string::npos != posAndRev.find("U")) { yPos = YPosition::Up; }
		if (string::npos != posAndRev.find("D")) { yPos = YPosition::Down; }

		int w, h;
		GetGraphSize(img, &w, &h);
		this->drawBase = MyGE::Box2D(0, 0, w, h);

		if (XPosition::Left == xPos) { this->pos.x = 0; }
		else if (XPosition::Right == xPos) { this->pos.x = (float)ge->Resolution.x - w; }
		else { this->pos.x = (ge->Resolution.x - w) / 2.0f; }

		if (YPosition::Up == yPos) { this->pos.y = 0; }
		else { this->pos.y = (float)ge->Resolution.y/2.0f-h; }
	}
	void Object::CreateOrReset(stringstream& ss_, CManager* pManager)
	{
		string taskName;
		ss_ >> taskName;
		auto p = ge->FindOneGN<Ev_Image::Object>("イベント画像",taskName);
		if (nullptr == p)
		{
			p = Object::Create(pManager);
			p->Set(taskName, ss_);
		}
		else
		{
			p->Set(taskName, ss_);
		}
	}

	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}