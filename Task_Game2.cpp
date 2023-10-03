//?X?e?[?W?Q?iVs?????j
#include"Task_Game2.h"
#include"Task_EventEngine.h"
namespace Game2 {
	Object::Object(CManager* pManager) : BTask(pManager)//?R???X?g???N?^
	{
		//?Q?[?????????????
		ge->gamestate = MyGE::MyGameEngine::GameState::Non;		
		//???
		ge->PlayMusicLoop(music, 70);
		//?w?i?????
		auto bg = GameBG::Object::Create(pManager);
		//?Q?[????????
		for (int y=0;y<chipsizeY;y++)
		{
			for (int x = 0; x < chipsizeX; x++)
			{
				auto board = Board::Object::Create(pManager);
				board->Setter(VGet(650+x * 180,300+y*190, 0));
			}
		}
		//?Q?[???????W
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
		auto target = ge->Find<Board::Object>("?Q?[????");
		for (auto it = target->begin(); it != target->end(); ++it)
		{
			Prepos[y][x] = (*it)->Getter();//?{?[?h??}?X????W
			x++;
			if(x>2)
			{
				y++;
				x = 0;
			}
		}

		//?v???C???????
		auto pl = Player::Object::Create(pManager);
		pl->SetBoardPos(Prepos);
		pl->Setter(Prepos[1][1]);


		//?v???C??HP?????	
		for (int i=0;i<playerHp;++i)
		{
			auto php = PlayerHp::Object::Create(pManager);	
		}
		auto targets2 = ge->Find<PlayerHp::Object>("?v???C??HP");
		int i=0,n=0;
		for (auto it = targets2->begin(); it != targets2->end(); it++)
		{
				(*it)->Setter(VGet(1550+i * 64, 900, 0));
				i++;
		}
		//?G?????
		auto en = Enemy::Object::Create(pManager);

		auto Enemy = ge->Find<Enemy::Object>("?G");
		auto it1 = Enemy->begin();
		(*it1)->SetBoardPos(Prepos);

		//?GHP?????	
		for (int i = 0; i < witchHp; ++i)
		{
			auto ehp = EnemyHp::Object::Create(pManager);	
		}

		auto enemyHp = ge->Find<EnemyHp::Object>("?G?l?~?[HP");
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
		//?Q?[???J?n???t???O
		this->GameStart = false;
	}

	Object::~Object()//?f?X?g???N?^ 
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

		auto targets = ge->Find<Player::Object>("?v???C??");
		auto it = targets->begin();
		if ((*it)->motion == BChara::Motion::Dead && ge->gamestate == MyGE::MyGameEngine::GameState::Non)
		{
			(*it)->Dead();
			ge->KillAll_G("?_???[?WUI");
			ge->KillAll_G("?G");
			ge->KillAll_G("?Q?[????");
			ge->KillAll_G("?w?i");
			ge->KillAll_G("?v???C??HP");
			ge->KillAll_G("?G?l?~?[HP");
			ge->KillAll_G("?v???C??");

			ge->gamestate = MyGE::MyGameEngine::GameState::GameOver;
			//?Q?[????V?[????s
			manager->scene = new GameOver::Object(manager);
			delete this;
		}
		if (ge->gamestate != MyGE::MyGameEngine::GameState::GameOver)
		{
			auto targets2 = ge->Find<Enemy::Object>("?G");
			auto it2 = targets2->begin();
			if ((*it2)->motion == BChara::Motion::Dead && ge->gamestate == MyGE::MyGameEngine::GameState::Non)
			{
				(*it2)->Dead();
				ge->KillAll_G("?_???[?WUI");
				ge->KillAll_G("?G");
				ge->KillAll_G("?Q?[????");
				ge->KillAll_G("?w?i");
				ge->KillAll_G("?v???C??HP");
				ge->KillAll_G("?G?l?~?[HP");
				ge->KillAll_G("?v???C??");
				ge->gamestate = MyGE::MyGameEngine::GameState::GameClear;
				//?Q?[????V?[????s
				manager->scene = new GameClear::Object(manager);
				delete this;
			}
		}
	}
	void Object::Render()
	{
	}
}
