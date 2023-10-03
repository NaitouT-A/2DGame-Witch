//イベント管理（メッセージ用）オブジェクト
#pragma once
#include "BChara.h"
class CManager;
namespace Ev_Message
{
	const  string  defGroupName = "メッセージ表示枠";	//グループ名
	class Object :public BTask
	{
		CManager* manager;
		int img[1];
		int bgNumber;
		VECTOR pos;
		string msgText;
		int timeCnt;
		int timeLimit;
		int mx, my;
		int mouse;
		bool PutM;

	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
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

		static void CreateOrReset(stringstream& ss_, CManager* pManager);

		void Set(const string& taskName_, stringstream& ss_);

		static Object::SP Create(CManager* pManager);
	};
}