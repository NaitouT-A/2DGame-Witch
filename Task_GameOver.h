//ゲームオーバーシーン
#pragma once
#include "Dxlib.h"
#include"SceneMgr.h"
#include"Task_Title.h"
constexpr int Player_ImageX = 8000;
constexpr int Player_ImageY = 3720;
namespace GameOver{
	class Object :public BTask
	{
		int graphic[70];
		int img[3];
		int anim;
		int anicnt;
		float y, yvec;
		bool ypos;
		//曲
		int music
		{
			music = LoadSoundMem("./data/sound/GameOver.mp3"),
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