//ゲームエンジン（タスク処理や共有する変数、関数）
#pragma once
#include "DxLib.h"
#include "vector"
#include "SceneMgr.h"
using namespace std;
constexpr int chipsizeX = 3;//ボードのX軸の個数
constexpr int chipsizeY = 3;//ボードのY軸の個数
constexpr int playerHp = 5;//プレイヤのHP
constexpr int slimeHp = 5;//スライムのHP
constexpr int witchHp = 20;//魔女HP
constexpr int tutorialHp = 3;//チュートリアル敵のHP
constexpr float lifeTime = 1;//魔法陣の生存時間
namespace MyGE {
	class MyGameEngine
	{
	public:
		//ゲーム全体で共有する変数はここに
		POINT Resolution; //画面の解像度
		enum class GameState {
			Non,
			GameClear,
			GameOver,
		};
		GameState gamestate;//ステージの状態
		enum class GameStage {
			Non,
			stage1,
			stage2,
			tutorial,
		};
		GameStage gamestage;//現在のゲームステージ
		bool End_;//終了するか否か

		int tutorialKey;//チュートリアルのストーリーキー
		//追加した変数を初期化
		MyGameEngine()
		{
			Resolution.x = SCREEN_WIDTH;
			Resolution.y = SCREEN_HEIGHT;
			gamestate = GameState::Non;
			gamestage = GameStage::Non;
			End_ = true;
		}
		//コンテナ
		vector<BTask::SP> taskA;
		vector<BTask::SP> addtask;
		//ループ
		void TUpDate();
		void TRender();
		//特定の名前のタスクをし、コンテナに入れる
		template <class V>
		shared_ptr<vector<shared_ptr<V>>>  Find(const  string& gn_)
		{
			shared_ptr<vector<shared_ptr<V>>>  w =
				shared_ptr<vector<shared_ptr<V>>>(new vector<shared_ptr<V>>());
			for (auto it = taskA.begin(); it != taskA.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName == gn_)
				{
					w->push_back(static_pointer_cast<V>((*it)));
				}
			}
			for (auto it = addtask.begin(); it != addtask.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName == gn_)
				{
					w->push_back(static_pointer_cast<V>((*it)));
				}
			}
			return w;
		}
		//特定の種類と固有の名前のタスクを探し、返す
		template <class T>
		shared_ptr<T> FindOneGN(const  string& gn_, const  string& n_)
		{
			for (auto it = taskA.begin(); it != taskA.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->name != n_) { continue; }
				if ((*it)->GroupName == gn_)
				{
					return static_pointer_cast<T>((*it));
				}
			}
			for (auto it = addtask.begin(); it != addtask.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->name != n_) { continue; }
				if ((*it)->GroupName == gn_)
				{
					return static_pointer_cast<T>((*it));
				}
			}
			return nullptr;
		}
		//特定の種類のタスクを探し、返す
		template <class T>
		shared_ptr<T> FindOne(const  string& gn_)
		{
			for (auto it = taskA.begin(); it != taskA.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName == gn_)
				{
					return static_pointer_cast<T>((*it));
				}
			}
			for (auto it = addtask.begin(); it != addtask.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName == gn_)
				{
					return static_pointer_cast<T>((*it));
				}
			}
			return nullptr;
		}
		//特定の種類のタスクをすべて排除する
		bool KillAll_G(const string& gn_)
		{
			bool rtv = false;
			for (auto it = taskA.begin(); it != taskA.end(); it++)
			{
				if ((*it)->GroupName != gn_) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName == gn_)
				{
					(*it)->Dead();
				}
				rtv = true;
			}
			return rtv;
		}
		//特定の種類のタスクをすべて停止させる
		bool StopAll_G(const string& gn_,bool m_)
		{
			bool rtv = false;
			for (auto it = taskA.begin(); it != taskA.end(); it++) {	//Kill状態の全てを削除する
				if ((*it) == nullptr) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName != gn_) { continue; }
				(*it)->Stop(m_);
				rtv = true;
			}
			return rtv;
		}
		//ゲームを終了させる
		bool GameEnd()
		{
			return End_;
		}
		//現在あるタスクをテキストに移す（終了時に削除）
		bool WriteDebugTaskList()
		{
			string filename = "./data/debug/tasklist.txt";

			ofstream file;
			file.open(filename, std::ios::out);
			if (file.fail())
			{
				return false;
			}
			else
			{
				for (auto it = taskA.begin(); it != taskA.end(); it++)
				{
					file << (*it)->GroupName << endl;
				}
				return true;
			}
		}
		//上で書いたテキストを削除
		int deleteDebugTextList(const char* fileName)
		{
			return !(remove(fileName));
		}
		//追加待ちのタスクに追加
		void Add(const BTask::SP& bs)
		{
			addtask.push_back(bs);
		}
		//追加待ちのタスクを実行タスクに移す
		void AddTask()
		{
			for (auto it = addtask.begin(); it != addtask.end(); it++)
			{
				taskA.push_back((*it));
			}
			addtask.erase(addtask.begin(),addtask.end());

		}
		//削除待ちの状態になったタスクを削除
		void KillTask()
		{
			auto itrNewEnd = std::remove_if(taskA.begin(), taskA.end()
				, [](BTask::SP s)->bool
				{ return s->taskstate == BTask::Taskstate::Kill; });
			taskA.erase(itrNewEnd, taskA.end());
		}
		//デバッグメッセージウィンドウ
		void DebugMessage(const char* text,const char* windowtext="デバッグメッセージ")
		{
			int btnid = MessageBox(NULL, text,windowtext, MB_OK);
		}
		//音楽を再生（musiclist[流したい曲],音量(0～255)）//ループ
		void PlayMusicLoop(int m_, int volume)
		{
			ChangeNextPlayVolumeSoundMem(volume, m_);

			PlaySoundMem(m_, DX_PLAYTYPE_LOOP);
		}
		//音楽を再生（musiclist[流したい曲],音量(0～255)）//ループ非対応
		void PlayMusicBack(int m_, int volume)
		{
			ChangeNextPlayVolumeSoundMem(volume, m_);

			PlaySoundMem(m_, DX_PLAYTYPE_BACK);
		}
		//音楽を再生（musiclist[流したい曲],音量(0～255)）//再生終わるまで動作を停止
		void PlayMusicJingle(int m_, int volume)
		{
			ChangeNextPlayVolumeSoundMem(volume, m_);

			PlaySoundMem(m_, DX_PLAYTYPE_NORMAL);
		}
	};
	//矩形クラス
	class Box2D
	{
	public:
		int x, y, w, h;
		Box2D()
			:x(0), y(0), w(0), h(0)
		{
		}
		Box2D(int x_, int y_, int w_, int h_)
			:x(x_), y(y_), w(w_), h(h_)
		{
		}
		Box2D(const Box2D& b_)
			:x(b_.x), y(b_.y), w(b_.w), h(b_.h)
		{
		}
		bool Hit(const Box2D b_)const
		{
			if (x < b_.x + b_.w &&
				b_.x < x + w &&
				y < b_.y + b_.h &&
				b_.y < y + h) {
				return true;
			}
			return false;
		}
		bool Hit(int x_, int y_, int w_, int h_)const
		{
			if (x < x_ + w_ &&
				x_ < x + w &&
				y < y_ + h_ &&
				y_ < y + h) {
				return true;
			}
			return false;
		}
		void Offset(float x_, float y_)
		{
			x += (int)x_;
			y += (int)y_;
		}
		void Offset(int x_, int y_)
		{
			x += x_;
			y += y_;
		}
		void Offset(VECTOR vec_)
		{
			x += vec_.x;
			y += vec_.y;
		}
		Box2D OffsetCopy(int x_, int y_) const
		{
			Box2D r(*this);
			r.Offset(x_, y_);
			return r;
		}
		Box2D OffsetCopy(float x_, float y_) const
		{
			Box2D r(*this);
			r.Offset(x_, y_);
			return r;
		}
		Box2D OffsetCopy(VECTOR vec_) const
		{
			Box2D r(*this);
			r.Offset(vec_.x, vec_.y);
			return r;
		}
	};

}
extern MyGE::MyGameEngine* ge;