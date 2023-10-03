//キャラクタクラス
#pragma once
#include "Dxmain.h"
#include "Dxlib.h"
#include"SceneMgr.h"
#include "MyGE.h"
class BChara:public BTask
{
public:
	using SP = shared_ptr<BChara>;
	using WP = weak_ptr<BChara>;
	//**********************************************************************************
	VECTOR pos;//ポジション
	int AnimTime;//アニメーション時間
	int AnimNum;//アニメーション番号
	float moveCnt;//行動カウンタ
	enum class Motion//モーション
	{
		unnon,
		Stand,
		BeforeAttack,
		Attack,
		Attack2,
		Attack3,
		Attack4,
		Hit,
		Dead,
	};
	Motion motion;

	bool updateMotion(Motion nm_);//モーション更新
	MyGE::Box2D hitbox;//当たり判定
	BChara(): BTask(manager)
	{
			pos = VGet(0, 0, 0),
			motion = Motion::unnon,
			AnimTime = 0,
			AnimNum = 0,
			hitbox = MyGE::Box2D(0, 0, 0, 0),
			moveCnt = 0;
	}

};