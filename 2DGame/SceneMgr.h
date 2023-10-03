//シーンの管理マネージャー
#pragma once
#include "Dxmain.h"
class CManager;
//シーンの基底クラス
class BTask
{
protected:
	CManager* manager;
private:

public:
	string  GroupName;	//種類名 
	string  name;       //固有名
	using SP = shared_ptr<BTask>;
	enum class Taskstate
	{
		Normal,
		Kill,
		Stop
	};
	Taskstate taskstate;//タスクの状態
	int Killcnt;        //削除予定のタスクのカウント

	BTask(CManager* pManager) { manager = pManager;};
	virtual ~BTask() {};

	//初期化
	bool Initialize(const  string& gn_)
	{
		this->GroupName = gn_;
		this->taskstate = Taskstate::Normal;
		this->Killcnt = 0;
		return true;
	}
	//破棄
	virtual void Dead() {};
	//描画
	virtual void Update() {};
	//更新
	virtual void Render() {};
	//停止
	void Stop(bool  f_ = true)
	{
		if (f_) { this->taskstate = BTask::Taskstate::Stop; }
		else { this->taskstate = BTask::Taskstate::Normal; }
	}
};
//シーン管理クラス
class CManager
{

public:
	//キー
	char* key;
	//今のシーンのポインタ
	BTask* scene=nullptr;

	CManager(char* pKey) { key = pKey; };
	~CManager() { delete scene; };
	char* GetKey() { return key; }
	//描画
	void Update() { scene->Update();};
	//更新
	void Render() { scene->Render(); };
};