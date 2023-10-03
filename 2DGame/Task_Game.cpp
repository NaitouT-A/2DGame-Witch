//�X�e�[�W�P�iVs�X���C���j
#include"Task_Game.h"
namespace Game {
	Object::Object(CManager* pManager) : BTask(pManager)//�R���X�g���N�^
	{
		//�Q�[���̏�Ԃ�ʏ�ɂ���
		ge->gamestate = MyGE::MyGameEngine::GameState::Non;		
		//�Đ�
		ge->PlayMusicLoop(music, 90);
		//�w�i�̐���
		auto bg = GameBG::Object::Create(pManager);
		//�Q�[���Ղ̐���
		for (int y=0;y<chipsizeY;y++)
		{
			for (int x = 0; x < chipsizeX; x++)
			{
				auto board = Board::Object::Create(pManager);
				board->Setter(VGet(650+x * 180,450+y*190, 0));
			}
		}
		//�Q�[���Ղ̍��W
		VECTOR Prepos[chipsizeY][chipsizeX];

		int x=0, y=0;
		auto target = ge->Find<Board::Object>("�Q�[����");
		for (auto it = target->begin(); it != target->end(); ++it)
		{
			Prepos[y][x] = (*it)->Getter();//�{�[�h�̃}�X�̍��W
			x++;
			if(x>2)
			{
				y++;
				x = 0;
			}
		}
		//�v���C���̐���
		auto pl = Player::Object::Create(pManager);
		pl->SetBoardPos(Prepos);
		pl->Setter(Prepos[1][1]);


		//�v���C��HP�̐���
		for (int i=0;i<playerHp;++i)
		{
			auto php = PlayerHp::Object::Create(pManager);		
		}
		auto targets2 = ge->Find<PlayerHp::Object>("�v���C��HP");
		int i=0;
		for (auto it = targets2->begin(); it != targets2->end(); it++)
		{
				(*it)->Setter(VGet(1550+i * 64, 100, 0));
				i++;
		}
		//�G�̐���
		auto en = Enemy2::Object::Create(pManager);

		auto Enemy = ge->Find<Enemy2::Object>("�G2");
		auto it1 = Enemy->begin();
		(*it1)->SetBoardPos(Prepos);
		//�Q�[���J�n���t���O
		this->GameStart = false;
		//�GHP�̐���
		for (int i = 0; i < slimeHp; ++i)
		{
			auto ehp = EnemyHp::Object::Create(pManager);		
		}
		auto enemyHp = ge->Find<EnemyHp::Object>("�G�l�~�[HP");
		i = 0;
		for (auto it = enemyHp->begin(); it != enemyHp->end(); it++)
		{
			(*it)->Setter(VGet(100 + i * 64, 150, 0));
			i++;
		}
	}

	Object::~Object()//�f�X�g���N�^ 
	{
		DeleteSoundMem(music);
	}


	void Object::Update()
	{
		if (this->GameStart==false)
		{
			auto ev = EventEngine::Object::Create_Mutex(manager);
			if (ev)
			{
				ev->Set("./data/event/eventSlime.txt");
			}
			this->GameStart = true;
		}

		auto targets = ge->Find<Player::Object>("�v���C��");
		auto it = targets->begin();
		if ((*it)->motion == BChara::Motion::Dead&& ge->gamestate == MyGE::MyGameEngine::GameState::Non)
		{
			(*it)->Dead();
			ge->KillAll_G("�_���[�WUI");
			ge->KillAll_G("�G2");
			ge->KillAll_G("�Q�[����");
			ge->KillAll_G("�w�i");
			ge->KillAll_G("�v���C��HP");
			ge->KillAll_G("�G�l�~�[HP");
			ge->KillAll_G("�v���C��");

			ge->gamestate = MyGE::MyGameEngine::GameState::GameOver;
			//�Q�[���ɃV�[���ڍs
			manager->scene = new GameOver::Object(manager);
			delete this;
		}
		if (ge->gamestate != MyGE::MyGameEngine::GameState::GameOver)
		{
			auto targets2 = ge->Find<Enemy2::Object>("�G2");
			auto it2 = targets2->begin();
			if ((*it2)->motion == BChara::Motion::Dead && ge->gamestate == MyGE::MyGameEngine::GameState::Non)
			{
				(*it2)->Dead();
				ge->KillAll_G("�_���[�WUI");
				ge->KillAll_G("�G2");
				ge->KillAll_G("�Q�[����");
				ge->KillAll_G("�w�i");
				ge->KillAll_G("�v���C��HP");
				ge->KillAll_G("�G�l�~�[HP");
				ge->KillAll_G("�v���C��");
				ge->gamestate = MyGE::MyGameEngine::GameState::GameClear;

				//�Q�[���ɃV�[���ڍs
				manager->scene = new GameClear::Object(manager);
				delete this;
			}
		}
	}
	void Object::Render()
	{

	}

}
