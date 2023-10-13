//ステージ２（Vs魔女）
#include"Task_Game2.h"
#include"Task_EventEngine.h"
namespace Game2 {
	Object::Object(CManager* pManager) : BTask(pManager)//コンストラクタ
	{
		//ゲームの状態を通常にする
		ge->gamestate = MyGE::MyGameEngine::GameState::Non;		
		//再生
		ge->PlayMusicLoop(music, 70);
		//背景の生成
		auto bg = GameBG::Object::Create(pManager);
		//ゲーム盤の生成
		for (int y=0;y<chipsizeY;y++)
		{
			for (int x = 0; x < chipsizeX; x++)
			{
				auto board = Board::Object::Create(pManager);
				board->Setter(VGet(650+x * 180,450+y*190, 0));
			}
		}
		//ゲーム盤の座標
		VECTOR Prepos[chipsizeY][chipsizeX];
		for (int y = 0; y < chipsizeY; y++)
		{
			for (int x = 0; x < chipsizeX; x++)
			{
				Prepos[y][x].x = 0;
				Prepos[y][x].y = 0;
			}
		}

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
		auto pl = Player::Object::Create(pManager);
		pl->SetBoardPos(Prepos);
		pl->Setter(Prepos[1][1]);


		//プレイヤHPの生成	
		for (int i=0;i<playerHp;++i)
		{
			auto php = PlayerHp::Object::Create(pManager);	
		}
		auto targets2 = ge->Find<PlayerHp::Object>("プレイヤHP");
		int i=0,n=0;
		for (auto it = targets2->begin(); it != targets2->end(); it++)
		{
				(*it)->Setter(VGet(1550+i * 64, 900, 0));
				i++;
		}
		//敵の生成
		auto en = Enemy::Object::Create(pManager);

		auto Enemy = ge->Find<Enemy::Object>("敵");
		auto it1 = Enemy->begin();
		(*it1)->SetBoardPos(Prepos);

		//敵HPの生成	
		for (int i = 0; i < witchHp; ++i)
		{
			auto ehp = EnemyHp::Object::Create(pManager);	
		}

		auto enemyHp = ge->Find<EnemyHp::Object>("エネミーHP");
		i = 0;
		for (auto it = enemyHp->begin(); it != enemyHp->end(); it++)
		{
			if (i % 5 == 0)
			{
				n++;
				i = 0;
			}
			(*it)->Setter(VGet(100 +i * 64, (n*64)+100, 0));
			i++;
		}
		//ゲーム開始時フラグ
		this->GameStart = false;
	}

	Object::~Object()//デストラクタ 
	{
		DeleteSoundMem(music);
	}

	void Object::Update()
	{	
		if (this->GameStart == false)
		{
			auto ev = EventEngine::Object::Create_Mutex(manager);
			if (ev)
			{
				ev->Set("./data/event/eventWitch.txt");
			}
			this->GameStart = true;
		}

		auto targets = ge->Find<Player::Object>("プレイヤ");
		auto it = targets->begin();
		if ((*it)->motion == BChara::Motion::Dead && ge->gamestate == MyGE::MyGameEngine::GameState::Non)
		{
			(*it)->Dead();
			ge->KillAll_G("ダメージUI");
			ge->KillAll_G("敵");
			ge->KillAll_G("ゲーム盤");
			ge->KillAll_G("背景");
			ge->KillAll_G("プレイヤHP");
			ge->KillAll_G("エネミーHP");
			ge->KillAll_G("プレイヤ");

			ge->gamestate = MyGE::MyGameEngine::GameState::GameOver;
			//ゲームにシーン移行
			manager->scene = new GameOver::Object(manager);
			delete this;
		}
		if (ge->gamestate != MyGE::MyGameEngine::GameState::GameOver)
		{
			auto targets2 = ge->Find<Enemy::Object>("敵");
			auto it2 = targets2->begin();
			if ((*it2)->motion == BChara::Motion::Dead && ge->gamestate == MyGE::MyGameEngine::GameState::Non)
			{
				(*it2)->Dead();
				ge->KillAll_G("ダメージUI");
				ge->KillAll_G("敵");
				ge->KillAll_G("ゲーム盤");
				ge->KillAll_G("背景");
				ge->KillAll_G("プレイヤHP");
				ge->KillAll_G("エネミーHP");
				ge->KillAll_G("プレイヤ");
				ge->gamestate = MyGE::MyGameEngine::GameState::GameClear;
				//ゲームにシーン移行
				manager->scene = new GameClear::Object(manager);
				delete this;
			}
		}
	}
	void Object::Render()
	{
	}
}
