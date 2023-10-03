//敵の攻撃判定用オブジェクト
#pragma once
#include "BChara.h"
class CManager;
namespace EAttack {
	const  string  defGroupName = "攻撃範囲";	//グループ名
	class Object :public BChara
	{
		CManager* manager;
		//画像データ格納
	public:
		bool isdead;
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
		Object(CManager*);
		//デストラクタ（インスタンス削除時に呼ばれる関数）
		~Object();
		//初期化（現状はgroupNameの代入のみ）
		bool  Initialize();

		void Update();
		//破棄申請
		void Dead();

		void Setter(VECTOR vec_);

		MyGE::Box2D Getter();

		VECTOR pGetter();

		static Object::SP Create(CManager* pManager);
	};
}