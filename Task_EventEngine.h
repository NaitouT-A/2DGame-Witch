//イベント管理用オブジェクト
#pragma once
#include "BChara.h"
class CManager;
namespace EventEngine
{
	const  string  defGroupName = "イベント実行";	//グループ名
	class Object :public BTask
	{
		CManager* manager;

		ifstream evFile;	
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		static WP instance;
		//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
		Object(CManager*);
		//デストラクタ（インスタンス削除時に呼ばれる関数）
		~Object();
		//初期化（現状はgroupNameの代入のみ）
		bool  Initialize();
		//描画の更新
		void Render();
		//更新
		void Update();
		//破棄申請
		void Dead();

		static Object::SP Create_Mutex(CManager* pManager);

		bool Set(const string& fPath_);

		bool ReadLine(string& lineT_);

		bool Execute(string& hs_, string& ds_);

		static Object::SP Create(CManager* pManager);
	};
}