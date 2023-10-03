//ステージ２（Vs魔女）
#pragma once
#include"DxLib.h"
#include"SceneMgr.h"
#include"Task_Title.h"
#include"Task_Player.h"
#include"Task_GameBG.h"
#include"Task_Board.h"
#include"Task_Enemy.h"
#include"Task_PlayerHp.h"
#include"Task_EnemyHp.h"
#include"Task_GameOver.h"
#include"Task_GameClear.h"
namespace Game2{
	class Object :public BTask
	{
		//曲
		int music
		{
			music = LoadSoundMem("./data/sound/VsWitch.mp3"),
		};
		bool GameStart;
	public:
		Object(CManager* pManager);
		~Object();
		void Update();
		void Render();
	};
}
