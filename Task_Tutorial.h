//チュートリアルステージ
#pragma once
#include"DxLib.h"
#include"SceneMgr.h"
#include"Task_Title.h"
#include"Task_TutorialPlayer.h"
#include"Task_GameBG.h"
#include"Task_Board.h"
#include"Task_TutorialEnemy.h"
#include"Task_PlayerHp.h"
#include"Task_EnemyHp.h"
#include"Task_GameOver.h"
#include"Task_GameClear.h"
#include"Task_EventEngine.h"
#include"Task_TutorialTask.h"
namespace Tutorial{
	class Object :public BTask
	{
		//曲
		int music
		{
			music = LoadSoundMem("./data/sound/Tutorial.mp3"),
		};
		bool GameStart;
	public:
		Object(CManager* pManager);
		~Object();
		void Update();
		void Render();
		void EventProgress(int key,CManager* pManager);
	};
}
