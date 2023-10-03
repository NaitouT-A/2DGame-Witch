//タイトルシーン
#include"Task_Title.h"
namespace Title {
	Object::Object(CManager* pManager) :BTask(pManager)
	{
		//再生
		ge->PlayMusicLoop(music[0], 90);
		//画像
		graphic[0]  = LoadGraph("./data/image/BookCoverSS.png");
		graphic[1]  = LoadGraph("./data/image/BookCoverGE.png");
		graphic[2]  = LoadGraph("./data/image/Title2.png");
		graphic[3]  = LoadGraph("./data/image/hukidasi.png");
		graphic[4]  = LoadGraph("./data/image/hondana.png");
		graphic[5]  = LoadGraph("./data/image/Player_Tatie.png");
		graphic[6]  = LoadGraph("./data/image/ロード画面.png");
		graphic[7]  = LoadGraph("./data/image/StartButton.png");
		graphic[8]  = LoadGraph("./data/image/StageSelect.png");
		graphic[9]  = LoadGraph("./data/image/StageSelect2.png");
		graphic[10] = LoadGraph("./data/image/Logo.png");
		graphic[11] = LoadGraph("./data/image/Cursor.png");
		//カウンタ
		this->cnt = 0;
		//画面のページ
		this->page = Page::Title;
		//キーボードが押されているか否か
		this->PutK = false;
		//ページ番号
		this->pageA = 0;
		//キャラの絵のポジション
		this->y = 0;
		//y軸の移動のベクトル
		this->yvec = 0.1;
		//ｙのフラグ
		this->ypos = false;
		//カーソル
		this->cursor = 0;
		//カーソルのサイズ
		this->b = MyGE::Box2D(0, 0, 0, 0);
	}
	Object::~Object() 
	{ 
		DeleteSoundMem(music[0]);
		DeleteSoundMem(music[1]);
		DeleteSoundMem(music[2]);
	};
	void Object::Update()
	{
		Anim();
		DecisionK();
	}

	void Object::Render()
	{	
		DrawExtendGraph(0, 0, 1920, 1080, graphic[2], TRUE);

		DrawExtendGraph(1000,y-100,1000+800,y+1132, graphic[5], TRUE);
		
		if (this->page == Page::Title)
		{
			DrawGraph(0, 0, graphic[10], TRUE);

			DrawGraph(35, 710, graphic[4],TRUE);

			DrawGraph(80 + zoom, 600 + zoom, graphic[0], TRUE);

			DrawGraph(80 + zoom2, 700 + zoom2, graphic[1], TRUE);
		}
		else if(this->page == Page::StageSelect)
		{
			DrawExtendGraph(0, 0, 405,226,graphic[10], TRUE);

			DrawExtendGraph(450+zoom3, 80+zoom3, 1050+zoom3, 600+zoom3, graphic[3], TRUE);

			DrawExtendGraph(180, 490, 980, 1120, graphic[8], TRUE);

			switch (pageA)
			{
				case 0:
					//ステージ1にシーン移行
					ge->gamestage = MyGE::MyGameEngine::GameStage::tutorial;
					DrawFormatString(525 + zoom3, 260 + zoom3, GetColor(0, 0, 0), "チュートリアル");
					DrawFormatString(600 + zoom3, 324 + zoom3, GetColor(0, 0, 0), "基本を学ぶ");
				break;
				case 1:
					//ステージ1にシーン移行
					ge->gamestage = MyGE::MyGameEngine::GameStage::stage1;
					DrawFormatString(600 + zoom3, 260 + zoom3, GetColor(0, 0, 0), "ステージ1");
					DrawFormatString(525 + zoom3, 324 + zoom3, GetColor(0, 0, 0), "スライムと戦う");
				break;
				case 2:
					//ステージ2にシーン移行
					ge->gamestage = MyGE::MyGameEngine::GameStage::stage2;
					DrawFormatString(600 + zoom3, 260 + zoom3, GetColor(0, 0, 0), "ステージ2");
					DrawFormatString(600 + zoom3, 324 + zoom3, GetColor(0, 0, 0), "魔女と戦う");
					break;
				case 3:
					DrawFormatString(690 + zoom3, 300 + zoom3, GetColor(0, 0, 0), "戻る");
				break;
			}
		}
		else
		{
			DrawExtendGraph(0, 0, 1920, 1080, graphic[6], TRUE);

			if (cnt < 30)
			{
				DrawExtendGraph(1500, 800, 1500 + 400, 800 + 300, graphic[7], TRUE);
			}
		}
		if (this->page!=Page::Intro)
		{
			if (cnt<30)
			{
				DrawExtendGraph(b.x, b.y, b.w, b.h, graphic[11], TRUE);
			}
		}
			
	}
	void Object::Anim()
	{
		y += 1 + yvec;
		if (ypos == false)
		{
			yvec += 0.02;
		}
		else
		{
			yvec -= 0.02;
		}

		if (yvec < -2.2)
		{
			ypos = false;
		}
		if (yvec > 0.2)
		{
			ypos = true;
		}
	}
	void Object::DecisionK()
	{
		zoom = -20;
		zoom2 = -20;
		zoom3 = -20;
		cnt++;
		if (cnt > 60)
			cnt = 0;
		switch(this->page)
		{
		case Page::Title:
			if (cursor==2)
			{
				cursor = 0;
			}
			if (cursor==0)
			{
				this->b = MyGE::Box2D(65,580,620,680);
			}
			if (cursor == 1)
			{
				this->b = MyGE::Box2D(65, 680, 620, 780);
			}
			if (manager->GetKey()[KEY_INPUT_UP] >= 1 && this->PutK == false)
			{
				this->PutK = true;
				cursor--;
				if (cursor <= 0)
				{
					cursor = 0;
				}
			}
			if (manager->GetKey()[KEY_INPUT_DOWN] >= 1 && this->PutK == false)
			{
				this->PutK = true;
				cursor++;
				if (cursor >= 1)
				{
					cursor = 1;
				}
			}
			if (manager->GetKey()[KEY_INPUT_RETURN]>=1 && this->PutK == false)
			{
				this->PutK = true;
				switch (this->cursor)
				{
					case 0:
						ge->PlayMusicBack(music[2], 90);
						this->page = Page::StageSelect;
						break;
					case 1:
						ge->PlayMusicBack(music[2], 90);
						//終了
						ge->End_ = false;
						break;
				}
			}
			if (manager->GetKey()[KEY_INPUT_DOWN] <=0&& manager->GetKey()[KEY_INPUT_UP] <= 0&&
				manager->GetKey()[KEY_INPUT_RETURN] <= 0 && this->PutK == true)
			{
				this->PutK = false;
			}
			break;
		case Page::StageSelect:

			if (cursor == 0)
			{
				this->b = MyGE::Box2D(250, 650, 550, 750);
			}
			if (cursor == 1)
			{
				this->b = MyGE::Box2D(630, 650, 930, 750);
			}
			if (cursor == 2)
			{
				this->b = MyGE::Box2D(450, 80, 1050, 480);
			}

			if (manager->GetKey()[KEY_INPUT_LEFT] >= 1 && this->PutK == false)
			{
				this->PutK = true;
				ge->PlayMusicBack(music[1], 90);
				this->pageA--;
				if (this->pageA <= 0) { this->pageA = 0; }

				cursor = 0;
			}
			if (manager->GetKey()[KEY_INPUT_RIGHT] >= 1 && this->PutK == false)
			{
				this->PutK = true;
				ge->PlayMusicBack(music[1], 90);
				this->pageA++;
				if (this->pageA >= 3) { this->pageA = 3; }

				cursor = 1;
			}
			if (manager->GetKey()[KEY_INPUT_UP] >= 1 && this->PutK == false)
			{
				this->PutK = true;
				ge->PlayMusicBack(music[1], 90);

				cursor=2;

			}
			if (manager->GetKey()[KEY_INPUT_DOWN] >= 1 && this->PutK == false)
			{
				this->PutK = true;
				ge->PlayMusicBack(music[1], 90);

				switch (this->pageA)
				{
					case 0:
						cursor = 0;
						break;
					case 1:
						cursor = 0;
						break;
					case 2:
						cursor = 1;
						break;
					case 3:
						cursor = 1;
						break;
				}

			}

			if (manager->GetKey()[KEY_INPUT_RETURN] >= 1 && this->PutK == false)
			{
				if (cursor == 2)
				{
					this->PutK = true;
					ge->PlayMusicBack(music[2], 90);
					switch (pageA)
					{
						case 0:
							this->page = Page::Intro;
							break;
						case 1:
							this->page = Page::Intro;
							break;
						case 2:
							this->page = Page::Intro;
							break;
						case 3:
							this->page = Page::Title;
							break;
					}
				}
			}

			if (manager->GetKey()[KEY_INPUT_LEFT] <= 0 && manager->GetKey()[KEY_INPUT_RIGHT] <= 0 &&
				manager->GetKey()[KEY_INPUT_UP] <= 0 && manager->GetKey()[KEY_INPUT_DOWN] <= 0 &&
				manager->GetKey()[KEY_INPUT_RETURN] <= 0 && this->PutK == true)
			{
				this->PutK = false;
			}
			break;
		case Page::Intro:		
			if (manager->GetKey()[KEY_INPUT_RETURN]>=1&& this->PutK == false)
			{
				this->PutK = true;
				//ゲームにシーン移行
				if (ge->gamestage == MyGE::MyGameEngine::GameStage::tutorial)
				{
					DeleteSoundMem(music[0]);
					DeleteSoundMem(music[1]);
					DeleteSoundMem(music[2]);

					manager->scene = new Tutorial::Object(manager);

					delete this;
					break;
				}
				//ゲームにシーン移行
				if (ge->gamestage == MyGE::MyGameEngine::GameStage::stage1)
				{
					DeleteSoundMem(music[0]);
					DeleteSoundMem(music[1]);
					DeleteSoundMem(music[2]);

					manager->scene = new Game::Object(manager);

					delete this;
					break;
				}
				//ゲームにシーン移行
				if (ge->gamestage == MyGE::MyGameEngine::GameStage::stage2)
				{
					DeleteSoundMem(music[0]);
					DeleteSoundMem(music[1]);
					DeleteSoundMem(music[2]);

					manager->scene = new Game2::Object(manager);

					delete this;
					break;
				}
			}
			if (manager->GetKey()[KEY_INPUT_RETURN] <= 0 && this->PutK == true)
			{
				this->PutK = false;
			}
			break;
		}
		
	}
}