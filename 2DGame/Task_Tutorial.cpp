//チュートリアルステージ
#include"Task_Tutorial.h"
namespace Tutorial {
	Object::Object(CManager* pManager) : BTask(pManager)//コンストラクタ
	{
		//ゲームの状態を通常にする
		ge->gamestate = MyGE::MyGameEngine::GameState::Non;	
		//チュートリアルのキーを0に
		ge->tutorialKey = 0;
		//再生
		ge->PlayMusicLoop(music, 90);
		//背景の生成
		auto bg = GameBG::Object::Create(pManager);
		for (int y=0;y<chipsizeY;y++)
		{
			for (int x = 0; x < chipsizeX; x++)
			{
				auto board = Board::Object::Create(pManager);//ゲーム盤の生成
				board->Setter(VGet(650+x * 180,450+y*190, 0));
			}
		}
		//ゲーム盤の座標
		VECTOR Prepos[chipsizeY][chipsizeX];

		int x=0, y=0;
		auto target = ge->Find<Board::Object>("ゲーム盤");
		for (auto it = target->begin(); it != target->end(); ++it)
		{
			Prepos[y][x] = (*it)->Getter();//ボードのマスの座標
			x++;
			if(x>2)
			{
				y++;
				x = 0;
			}
		}
		//プレイヤの生成
		auto pl = TutorialPlayer::Object::Create(pManager);
		pl->SetBoardPos(Prepos);
		pl->Setter(Prepos[1][1]);


		//プレイヤHPの生成
		for (int i=0;i<playerHp;++i)
		{
			auto php = PlayerHp::Object::Create(pManager);		
		}
		auto targets2 = ge->Find<PlayerHp::Object>("プレイヤHP");
		int i=0;
		for (auto it = targets2->begin(); it != targets2->end(); it++)
		{
				(*it)->Setter(VGet(1550+i * 64, 900, 0));
				i++;
		}
		//敵の生成
		auto en = TutorialEnemy::Object::Create(pManager);

		auto Enemy = ge->Find<TutorialEnemy::Object>("練習敵");
		auto it1 = Enemy->begin();
		(*it1)->SetBoardPos(Prepos);
		//ゲーム開始時フラグ
		this->GameStart = false;

		//敵HPの生成	
		for (int i = 0; i < tutorialHp; ++i)
		{
			auto ehp = EnemyHp::Object::Create(pManager);	
		}

		auto enemyHp = ge->Find<EnemyHp::Object>("エネミーHP");
		i = 0;
		for (auto it = enemyHp->begin(); it != enemyHp->end(); it++)
		{
			(*it)->Setter(VGet(225 + i * 64, 150, 0));
			i++;
		}
	}

	Object::~Object() 
	{
		DeleteSoundMem(music);
	}


	void Object::Update()
	{
		if (this->GameStart==false)
		{
			EventProgress(ge->tutorialKey, manager);
			this->GameStart = true;
		}
		auto event = ge->Find<EventEngine::Object>("イベント実行");

		if(ge->tutorialKey==1&&event->size()==0){ EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 8 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 14 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 18 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 20 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		auto targets = ge->Find<TutorialPlayer::Object>("チュートリアルプレイヤ");
		auto it = targets->begin();

		if (ge->gamestate == MyGE::MyGameEngine::GameState::GameOver)
		{
			(*it)->Dead();
			ge->KillAll_G("ミッション");
			ge->KillAll_G("ダメージUI");
			ge->KillAll_G("練習敵");
			ge->KillAll_G("ゲーム盤");
			ge->KillAll_G("背景");
			ge->KillAll_G("攻撃範囲");
			ge->KillAll_G("プレイヤHP");
			ge->KillAll_G("エネミーHP");
			ge->KillAll_G("チュートリアルプレイヤ");
			//ゲームにシーン移行
			manager->scene = new GameOver::Object(manager);
			delete this;
		}

	}
	void Object::Render()
	{
		
	}
	void Object::EventProgress(int key, CManager* pManager)
	{
		EventEngine::Object::SP ev;
		TutorialTask::Object::SP task;
		TutorialEnemy::Object::SP en;
		switch(key)
		{
		case 0:
			ev = EventEngine::Object::Create_Mutex(pManager);
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0001.txt");
			}
			ge->tutorialKey +=1;
			break;
		case 1:
			ev = EventEngine::Object::Create_Mutex(pManager);
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0002.txt");
			}
			task = TutorialTask::Object::Create(pManager);
			ge->tutorialKey += 1;
			break;
		case 8:
			ev = EventEngine::Object::Create_Mutex(pManager);
			ge->KillAll_G("ミッション");
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0003.txt");
			}	
			task = TutorialTask::Object::Create(pManager);
			ge->tutorialKey += 1;
			break;
		case 14:
			ev = EventEngine::Object::Create_Mutex(pManager);
			ge->KillAll_G("ミッション");
			ge->KillAll_G("攻撃範囲");
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0004.txt");
			}
			ge->tutorialKey += 1;
			task = TutorialTask::Object::Create(pManager);
			break;
		case 18:
			ev = EventEngine::Object::Create_Mutex(pManager);
			ge->KillAll_G("ミッション");
			ge->KillAll_G("攻撃範囲");
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0005.txt");
			}
			ge->tutorialKey += 1;
			break;
		case 20:
			ge->gamestate = MyGE::MyGameEngine::GameState::GameClear;
			ge->KillAll_G("ミッション");
			ge->KillAll_G("攻撃範囲");
			ge->KillAll_G("ダメージUI");
			ge->KillAll_G("練習敵");
			ge->KillAll_G("ゲーム盤");
			ge->KillAll_G("背景");
			ge->KillAll_G("攻撃範囲");
			ge->KillAll_G("プレイヤHP");
			ge->KillAll_G("エネミーHP");
			ge->KillAll_G("チュートリアルプレイヤ");
			//ゲームにシーン移行
			manager->scene = new GameClear::Object(manager);
			delete this;
			break;
		}
	}

}
