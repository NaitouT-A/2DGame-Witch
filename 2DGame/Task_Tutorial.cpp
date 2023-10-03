//�`���[�g���A���X�e�[�W
#include"Task_Tutorial.h"
namespace Tutorial {
	Object::Object(CManager* pManager) : BTask(pManager)//�R���X�g���N�^
	{
		//�Q�[���̏�Ԃ�ʏ�ɂ���
		ge->gamestate = MyGE::MyGameEngine::GameState::Non;	
		//�`���[�g���A���̃L�[��0��
		ge->tutorialKey = 0;
		//�Đ�
		ge->PlayMusicLoop(music, 90);
		//�w�i�̐���
		auto bg = GameBG::Object::Create(pManager);
		for (int y=0;y<chipsizeY;y++)
		{
			for (int x = 0; x < chipsizeX; x++)
			{
				auto board = Board::Object::Create(pManager);//�Q�[���Ղ̐���
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
		auto pl = TutorialPlayer::Object::Create(pManager);
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
				(*it)->Setter(VGet(1550+i * 64, 900, 0));
				i++;
		}
		//�G�̐���
		auto en = TutorialEnemy::Object::Create(pManager);

		auto Enemy = ge->Find<TutorialEnemy::Object>("���K�G");
		auto it1 = Enemy->begin();
		(*it1)->SetBoardPos(Prepos);
		//�Q�[���J�n���t���O
		this->GameStart = false;

		//�GHP�̐���	
		for (int i = 0; i < tutorialHp; ++i)
		{
			auto ehp = EnemyHp::Object::Create(pManager);	
		}

		auto enemyHp = ge->Find<EnemyHp::Object>("�G�l�~�[HP");
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
		auto event = ge->Find<EventEngine::Object>("�C�x���g���s");

		if(ge->tutorialKey==1&&event->size()==0){ EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 8 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 14 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 18 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		if (ge->tutorialKey == 20 && event->size() == 0) { EventProgress(ge->tutorialKey, manager); }
		auto targets = ge->Find<TutorialPlayer::Object>("�`���[�g���A���v���C��");
		auto it = targets->begin();

		if (ge->gamestate == MyGE::MyGameEngine::GameState::GameOver)
		{
			(*it)->Dead();
			ge->KillAll_G("�~�b�V����");
			ge->KillAll_G("�_���[�WUI");
			ge->KillAll_G("���K�G");
			ge->KillAll_G("�Q�[����");
			ge->KillAll_G("�w�i");
			ge->KillAll_G("�U���͈�");
			ge->KillAll_G("�v���C��HP");
			ge->KillAll_G("�G�l�~�[HP");
			ge->KillAll_G("�`���[�g���A���v���C��");
			//�Q�[���ɃV�[���ڍs
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
			ge->KillAll_G("�~�b�V����");
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0003.txt");
			}	
			task = TutorialTask::Object::Create(pManager);
			ge->tutorialKey += 1;
			break;
		case 14:
			ev = EventEngine::Object::Create_Mutex(pManager);
			ge->KillAll_G("�~�b�V����");
			ge->KillAll_G("�U���͈�");
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0004.txt");
			}
			ge->tutorialKey += 1;
			task = TutorialTask::Object::Create(pManager);
			break;
		case 18:
			ev = EventEngine::Object::Create_Mutex(pManager);
			ge->KillAll_G("�~�b�V����");
			ge->KillAll_G("�U���͈�");
			if (ev)
			{
				ev->Set("./data/event/Tutorial/Tutorial0005.txt");
			}
			ge->tutorialKey += 1;
			break;
		case 20:
			ge->gamestate = MyGE::MyGameEngine::GameState::GameClear;
			ge->KillAll_G("�~�b�V����");
			ge->KillAll_G("�U���͈�");
			ge->KillAll_G("�_���[�WUI");
			ge->KillAll_G("���K�G");
			ge->KillAll_G("�Q�[����");
			ge->KillAll_G("�w�i");
			ge->KillAll_G("�U���͈�");
			ge->KillAll_G("�v���C��HP");
			ge->KillAll_G("�G�l�~�[HP");
			ge->KillAll_G("�`���[�g���A���v���C��");
			//�Q�[���ɃV�[���ڍs
			manager->scene = new GameClear::Object(manager);
			delete this;
			break;
		}
	}

}
