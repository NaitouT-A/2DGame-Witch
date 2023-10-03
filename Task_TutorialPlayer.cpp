//チュートリアルプレイヤー用オブジェクト
#pragma once
#include "Task_TutorialPlayer.h"
#include "Task_Enemy.h"
#include "Task_Enemy2.h"
#include "Task_Board.h"
#include "Task_PlayerHp.h"
#include "Task_DamagedOverray.h"
constexpr float Player_Speed = 1.0f;
constexpr int Player_ImageX = 8000;
constexpr int Player_ImageY = 3720;
namespace TutorialPlayer
{
	Object::Object(CManager* pManager)
	{
		//CManagerのアドレス格納
		manager = pManager;
		//画像データ格納
		LoadDivGraph("./data/image/PlayerX.png", 70, 10, 7, Player_ImageX / 10, Player_ImageY / 7, graphic);
		//キーが押されているか否か
		this->Keycheck = false;
		//モーション
		this->motion = Motion::Stand;
		//攻撃しているか否か
		this->isAttack = false;
		//攻撃力
		this->ATK = 0;
		//当たり判定
		this->hitbox = MyGE::Box2D(+100, +40, 130, 180);
		this->HitCnt = 0;
		//当たっているか否か
		this->isHit = false;
		//HP
		this->Hp = playerHp;
		//効果音
		this->sound[0] = LoadSoundMem("./data/sound/SE_Damage.mp3");
		this->sound[1] = LoadSoundMem("./data/sound/SE_Spell.mp3");
		//躱した判定
		this->dodge = false;
	}
	Object::~Object()
	{
		DeleteSoundMem(sound[0]);
		DeleteSoundMem(sound[1]);
	}
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName);
		return true;
	}
	void Object::Dead()
	{
		//削除待ちにする
		this->taskstate = Taskstate::Kill;
		this->Killcnt += 1;
	}
	void Object::Update()
	{
		if (ge->gamestate==MyGE::MyGameEngine::GameState::Non)
		{
			MyGE::Box2D me = this->hitbox.OffsetCopy(this->pos);

			auto EnemyA = ge->Find<EAttack::Object>("攻撃範囲");
			for (auto it = EnemyA->begin(); it != EnemyA->end(); it++)
			{
				MyGE::Box2D me = this->hitbox.OffsetCopy(this->pos);
				MyGE::Box2D you = (*it)->hitbox.OffsetCopy((*it)->pos);

				if (you.Hit(me))
				{
					this->isHit = true;
				}
			}

			if (this->Hp <= 0)
			{
				this->Hp = 0;
				this->motion = Motion::Dead;
				ge->gamestate = MyGE::MyGameEngine::GameState::GameOver;
			}
			if (this->motion != Motion::Dead)
			{
				Object::ConutAnimTime();
				this->Think();
				this->Move();
			}
			if (this->isAttack)
			{
				this->ATK = 1;
			}
			else
				this->ATK = 0;
		}
		if (ge->tutorialKey==19)
		{
			ge->tutorialKey += 1;
		}
	}
	void Object::Render()
	{
		//読みこんだグラフィックを回転描画
		DrawExtendGraph(this->pos.x,this->pos.y, this->pos.x+400, this->pos.y+224,graphic[this->AnimNum], TRUE);
	}
	void Object::ConutAnimTime()
	{
		this->AnimTime++;
		if (this->AnimTime >= 69)
		{
			this->AnimTime = 0;
		}
		int animtable[] = { 0,1,2,3,4,5,0 };
		this->AnimNum = animtable[this->AnimTime / 10];
	}
	void Object::SetAttack(bool b)
	{
		this->isAttack = b;
	}
	void Object::Setter(VECTOR vec_)
	{
		this->pos.x = vec_.x-80;
		this->pos.y = vec_.y;
	}
	int Object::getATK()
	{
		return this->ATK;
	}
	void Object::SetBoardPos(VECTOR vec_[3][3])
	{
		for (int y=0;y<3;++y)
		{
			for (int x=0;x<3;++x)
			{
				this->board[y][x]=vec_[y][x];
			}
		}
	}
	void Object::Think()
	{
		BChara::Motion nm = this->motion;
		auto ea = ge->Find<EAttack::Object>("攻撃範囲");
		switch (nm)
		{
		case Motion::Stand:
			if (this->isHit&&ge->tutorialKey != 15)
			{ 
				auto di = DamagedOverray::Object::Create(manager);

				auto Php = ge->Find<PlayerHp::Object>("プレイヤHP");
				for (auto it = Php->begin(); it != Php->end(); it++)
				{
					(*it)->Dead();
					break;
				}
				nm = Motion::Hit; 
				this->Hp--; 
			}
			else if (ea->size()>0&&this->dodge==false)
			{
				this->dodge = true;
				if (ge->tutorialKey >= 9 && ge->tutorialKey < 15) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 14) { ge->tutorialKey = 14; }
				}
			}
			if (ea->size() == 0) { this->dodge = false; }
			break;
		case Motion::Hit:
			break;
		case Motion::Dead:
			
			break;
		}
		this->updateMotion(nm);
	}
	void Object::Move()
	{
		switch (this->motion)
		{
		case Motion::Stand:
			break;
		case Motion::Attack:
			break;
		case Motion::Hit:
			this->HitCnt++;
			if(this->HitCnt==1){ ge->PlayMusicBack(sound[0], 90); }
			if (this->HitCnt / 60 > 0.8) { this->HitCnt = 0; this->motion = Motion::Stand;  this->isHit = false;
			}
			break;
		case Motion::Dead:
			break;
		}
		if (this->motion != Motion::Dead)
		{
#pragma region Move
			if (manager->GetKey()[KEY_INPUT_LEFT] > 0 && manager->GetKey()[KEY_INPUT_UP] && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[0][0]);
			}
			else if (manager->GetKey()[KEY_INPUT_UP] > 0 && manager->GetKey()[KEY_INPUT_RIGHT] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[0][2]);
			}
			else if (manager->GetKey()[KEY_INPUT_DOWN] > 0 && manager->GetKey()[KEY_INPUT_RIGHT] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[2][2]);
			}
			else if (manager->GetKey()[KEY_INPUT_DOWN] > 0 && manager->GetKey()[KEY_INPUT_LEFT] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[2][0]);
			}
			else if (manager->GetKey()[KEY_INPUT_LEFT] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[1][0]);
			}
			else if (manager->GetKey()[KEY_INPUT_RIGHT] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[1][2]);
			}
			else if (manager->GetKey()[KEY_INPUT_UP] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2 && ge->tutorialKey < 8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[0][1]);
			}
			else if (manager->GetKey()[KEY_INPUT_DOWN] > 0 && !Keycheck)
			{
				if (ge->tutorialKey >= 2&&ge->tutorialKey<8) {
					ge->tutorialKey += 1;
					if (ge->tutorialKey > 8) { ge->tutorialKey = 8; }
				}
				Keycheck = true;
				Setter(board[2][1]);
			}
			if (manager->GetKey()[KEY_INPUT_Z] > 0 && !this->isAttack&&ge->tutorialKey>=15)
			{
				Keycheck = true;
				ge->PlayMusicBack(sound[1], 90);
				auto cl = TutorialCircle::Object::Create(manager);//プレイヤの生成
				auto targets = ge->Find<TutorialCircle::Object>("練習魔法陣");
				auto it = targets->begin();
				if (!this->isAttack)
					this->SetAttack(true);
			}
		}

		if (manager->GetKey()[KEY_INPUT_DOWN] <= 0 &&
			manager->GetKey()[KEY_INPUT_UP] <= 0 &&
			manager->GetKey()[KEY_INPUT_RIGHT] <= 0 &&
			manager->GetKey()[KEY_INPUT_LEFT] <= 0)
		{
			Keycheck = false;
			Setter(board[1][1]);
		}
#pragma endregion Move
	}
	Object::SP Object::Create(CManager* pManager)
	{
		Object::SP ob = Object::SP(new Object(pManager));
		ob->Initialize();
		ge->Add(ob);
		return ob;
	}
}