//エフェクト生成用オブジェクト
#pragma once
#include "BChara.h"
#include "Task_EffectBomb.h"
class CManager;
namespace EffectCreate {
	const  string  defGroupName = "エフェクト生成";	//グループ名
	class Object :public BChara
	{
		CManager* manager;
		bool create;
		//画像データ格納
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
		Object(CManager*);
		//デストラクタ（インスタンス削除時に呼ばれる関数）
		~Object();
		//描画の更新
		void Render();
		//更新
		void Update();

		//初期化（現状はgroupNameの代入のみ）
		bool  Initialize();
		//破棄申請
		void Dead();

		static Object::SP Create(CManager* pManager);

		enum EFFECTTYPE {
			BOMB,
			Magic
		};
		void CreateEffect(Object::EFFECTTYPE type, VECTOR p);
		//共有する変数******************
		bool isdead;
	};
}