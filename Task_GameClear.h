//ゲームクリアシーン
#pragma once
#include "Dxlib.h"
#include"SceneMgr.h"
#include"Task_Title.h"
namespace GameClear{
	class Object :public BTask
	{
		int graphic[70];
		int anim;
		int anicnt;
		int img[3];
		float y, yvec;
		bool ypos;
		//曲
		int music
		{
			music = LoadSoundMem("./data/sound/GameClear.mp3"),
		};
	public:
		Object(CManager* pManager);
		~Object() {
			DeleteSoundMem(music);
		};
		void Render();
		void Update();
		void Anim();
	};
}