#pragma once
#include "Dxlib.h"
#include"SceneMgr.h"
#include"Task_Title.h"
#include"Task_Game.h"
#include"Task_GameIntro.h"
namespace StageSelect{
	class Object :public BTask
	{
		enum class Menu {
			Non,
			Title,
			Stage1,
			Stage2,
			Stage3,
			GameEnd,
		};
		Menu menu;
		int page;
		int graphic[3];
		int mx, my;
		int mouse;
		int zoom, zoom2,zoom3;
	public:
		Object(CManager* pManager);
		~Object();
		void Render();
		void Update();
		void Select();
		void Decision();
	};
}