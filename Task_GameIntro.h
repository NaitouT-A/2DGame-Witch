#pragma once
#include "BChara.h"
#include "Task_Game.h"
#include "Task_Game2.h"
class CManager;
namespace GameIntro {
	class Object :public BTask
	{
		CManager* manager;
		//画像データ格納
		int graphic[2];

		int cnt;
		int mx, my;
		int mouse;
	public:
		//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
		Object(CManager* pManager) :BTask(pManager)
		{
			manager = pManager;
			//画像データ格納
			graphic[0] = LoadGraph("./data/image/ロード画面.png");

			graphic[1] = LoadGraph("./data/image/StartButton.png");
			cnt = 0;
		};
		//デストラクタ（インスタンス削除時に呼ばれる関数）
		~Object() {};
		//描画の更新
		void Render();
		//更新
		void Update();
	};
}