//敵（魔女）オブジェクト
#pragma once
#include "BChara.h"
#include "Task_EffectCreate.h"
#include "Task_EAttack.h"
#include "Task_EnemyHp.h"
class CManager;
class EffectCreate::Object;
namespace Enemy {
	const  string  defGroupName = "敵";	//グループ名
	class Object :public BChara
	{
		CManager* manager;
		//画像データ格納
		int graphic[50];
		//*********************
		int AnimTime;
		int AnimNum;
		int Hp;
		int damage;
		VECTOR DeafultPos;
		VECTOR board[3][3];
		int AttackPos[3][3];
		int AttackKey;
		bool create[3][3];
		int preattackkey = 0;
	public:
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;

		//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
		Object(CManager*);
		//デストラクタ（インスタンス削除時に呼ばれる関数）
		~Object();
		//初期化（現状はgroupNameの代入のみ）
		bool  Initialize();
		//破棄申請
		void Dead();
		//描画の更新
		void Render();
		//更新
		void Update();

		void ConutAnimTime();

		void Think();

		void Move();

		void SetBoardPos(VECTOR vec_[3][3]);

		void Setter(VECTOR vec_);

		void SetDamage(int damage_);

		MyGE::Box2D Getter();

		int Anim();

		bool AttackLoad(const string& fpath_);

		static Object::SP Create(CManager* pManager);
	};
}