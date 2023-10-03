//魔法陣（プレイヤー攻撃用）オブジェクト
#pragma once
#include "BChara.h"
class CManager;

namespace TutorialCircle {
	const  string  defGroupName = "練習魔法陣";	//グループ名
	class Object :public BChara
	{
		CManager* manager;
		//画像データ格納
		int graphic;
		int alivetime;
		int invoke;
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		bool isdead;
		bool isHit;
		bool create;
		//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
		Object(CManager*);
		//デストラクタ（インスタンス削除時に呼ばれる関数）
		~Object();
		//初期化（現状はgroupNameの代入のみ）
		bool  Initialize();
		//破棄申請
		void Dead();
		//破棄
		void Finalize();
		//描画の更新
		void Render();
		//更新
		void Update();

		bool isDead();

		static Object::SP Create(CManager* pManager);
	};
}