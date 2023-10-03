//プレイヤー用オブジェクト
#pragma once
#include "BChara.h"
#include "Task_Circle.h"
class CManager;
namespace Player
{
	const  string  defGroupName = "プレイヤ";	//グループ名
	class Object :public BChara
	{
		CManager* manager;
		//画像データ格納
		int graphic[70];
		bool Keycheck;
		VECTOR board[3][3];
		bool isAttack;
		int  ATK;
		int HitCnt;
		int Hp;
		int sound[2];
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
		
		void Setter(VECTOR vec_);

		void SetBoardPos(VECTOR vec_[3][3]);

		void SetAttack(bool b);

		int getATK();

		void ConutAnimTime();

		void Think();

		void Move();

		static Object::SP Create(CManager* pManager);
		//共有する変数*******************************
		bool isHit;
	};
}