//タイトルシーン
#pragma once
#include "Dxlib.h"
#include"SceneMgr.h"
#include "MyGE.h"
#include "Task_Game.h"
#include "Task_Game2.h"
#include "Task_Tutorial.h"
namespace Title{
	class Object :public BTask
	{
		//曲
		int music[3]
		{
			music[0] = LoadSoundMem("./data/sound/Title.mp3"),
			music[1] = LoadSoundMem("./data/sound/SE_Paper.mp3"),
			music[2] = LoadSoundMem("./data/sound/SE_Click.mp3")
		};
		enum class Page
		{
			Title,
			StageSelect,
			Intro,
		};
		Page page;
		int graphic[12];
		int mx, my;
		int mouse;
		float y, yvec;
		bool ypos;
		int zoom,zoom2,zoom3;
		int cnt;
		bool PutK;
		int pageA;
		int cursor;
		MyGE::Box2D b;
	public:
		Object(CManager* pManager);
		~Object();
		void Update();
		void Render();
		void Anim();
		void DecisionK();
	};
}