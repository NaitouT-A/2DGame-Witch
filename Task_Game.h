//�X�e�[�W�P�iVs�X���C���j
#pragma once
#include"DxLib.h"
#include"SceneMgr.h"
#include"Task_Title.h"
#include"Task_Player.h"
#include"Task_GameBG.h"
#include"Task_Board.h"
#include"Task_Enemy2.h"
#include"Task_PlayerHp.h"
#include"Task_EnemyHp.h"
#include"Task_GameOver.h"
#include"Task_GameClear.h"
#include"Task_EventEngine.h"
namespace Game{
	class Object :public BTask
	{
		//��
		int music
		{
			music = LoadSoundMem("./data/sound/VsSlime.mp3"),
		};
		bool GameStart;
	public:
		Object(CManager* pManager);
		~Object();
		void Update();
		void Render();

	};
}
