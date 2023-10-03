//イベント管理（フェードイン・アウト）オブジェクト
#pragma once
#include "BChara.h"
class CManager;
namespace Ev_FadeInOut
{
	const  string  defGroupName = "フェードIO";	//グループ名
	class Object :public BTask
	{
		CManager* manager;

		int img;
		VECTOR pos;
		enum class Mode { Out, In,Non };
		Mode mode;
		int cnt;
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

		static void CreateOrFadeIn(stringstream& ss_, CManager* pManager);

		void Set(stringstream& ss_);

		static Object::SP Create(CManager* pManager);
	};
}