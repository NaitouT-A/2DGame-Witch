//ゲーム盤（マス単位）オブジェクト
#pragma once
#include "Task_Board.h"
constexpr int Image_X = 230;
constexpr int Image_Y = 230;
namespace Board
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像
		graphic = LoadGraph("./data/image/map.png");
		//ポジション
		this->pos.x = 100;
		this->pos.y = 100;
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

	}
	void Object::Render()
	{
		DrawExtendGraph(this->pos.x, this->pos.y,this->pos.x+Image_X,this->pos.y+Image_Y,graphic, TRUE);
	}
	VECTOR Object::Getter()
	{
		return this->pos;
	}
	void Object::Setter(VECTOR vec_)
	{
		this->pos.x = vec_.x;
		this->pos.y = vec_.y;
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}