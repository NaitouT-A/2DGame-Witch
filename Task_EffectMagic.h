//エフェクト（魔法）オブジェクト
#pragma once
#include "BChara.h"
class CManager;
namespace EffectMagic {
	const  string  defGroupName = "ボム";	//グループ名
	class Object :public BChara
	{
		CManager* manager;
		//画像データ格納
		int graphic[15];
		int sound;
		//*****************************
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

		void Setter(VECTOR pos_);

		//初期化（現状はgroupNameの代入のみ）
		bool  Initialize();
		//破棄申請
		void Dead();

		static Object::SP Create(CManager* pManager);
		//共有する変数******************
	};
}