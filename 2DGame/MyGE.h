//�Q�[���G���W���i�^�X�N�����⋤�L����ϐ��A�֐��j
#pragma once
#include "DxLib.h"
#include "vector"
#include "SceneMgr.h"
using namespace std;
constexpr int chipsizeX = 3;//�{�[�h��X���̌�
constexpr int chipsizeY = 3;//�{�[�h��Y���̌�
constexpr int playerHp = 5;//�v���C����HP
constexpr int slimeHp = 5;//�X���C����HP
constexpr int witchHp = 20;//����HP
constexpr int tutorialHp = 3;//�`���[�g���A���G��HP
constexpr float lifeTime = 1;//���@�w�̐�������
namespace MyGE {
	class MyGameEngine
	{
	public:
		//�Q�[���S�̂ŋ��L����ϐ��͂�����
		POINT Resolution; //��ʂ̉𑜓x
		enum class GameState {
			Non,
			GameClear,
			GameOver,
		};
		GameState gamestate;//�X�e�[�W�̏��
		enum class GameStage {
			Non,
			stage1,
			stage2,
			tutorial,
		};
		GameStage gamestage;//���݂̃Q�[���X�e�[�W
		bool End_;//�I�����邩�ۂ�

		int tutorialKey;//�`���[�g���A���̃X�g�[���[�L�[
		//�ǉ������ϐ���������
		MyGameEngine()
		{
			Resolution.x = SCREEN_WIDTH;
			Resolution.y = SCREEN_HEIGHT;
			gamestate = GameState::Non;
			gamestage = GameStage::Non;
			End_ = true;
		}
		//�R���e�i
		vector<BTask::SP> taskA;
		vector<BTask::SP> addtask;
		//���[�v
		void TUpDate();
		void TRender();
		//����̖��O�̃^�X�N�����A�R���e�i�ɓ����
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
		//����̎�ނƌŗL�̖��O�̃^�X�N��T���A�Ԃ�
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
		//����̎�ނ̃^�X�N��T���A�Ԃ�
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
		//����̎�ނ̃^�X�N�����ׂĔr������
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
		//����̎�ނ̃^�X�N�����ׂĒ�~������
		bool StopAll_G(const string& gn_,bool m_)
		{
			bool rtv = false;
			for (auto it = taskA.begin(); it != taskA.end(); it++) {	//Kill��Ԃ̑S�Ă��폜����
				if ((*it) == nullptr) { continue; }
				if ((*it)->Killcnt > 0) { continue; }
				if ((*it)->GroupName != gn_) { continue; }
				(*it)->Stop(m_);
				rtv = true;
			}
			return rtv;
		}
		//�Q�[�����I��������
		bool GameEnd()
		{
			return End_;
		}
		//���݂���^�X�N���e�L�X�g�Ɉڂ��i�I�����ɍ폜�j
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
		//��ŏ������e�L�X�g���폜
		int deleteDebugTextList(const char* fileName)
		{
			return !(remove(fileName));
		}
		//�ǉ��҂��̃^�X�N�ɒǉ�
		void Add(const BTask::SP& bs)
		{
			addtask.push_back(bs);
		}
		//�ǉ��҂��̃^�X�N�����s�^�X�N�Ɉڂ�
		void AddTask()
		{
			for (auto it = addtask.begin(); it != addtask.end(); it++)
			{
				taskA.push_back((*it));
			}
			addtask.erase(addtask.begin(),addtask.end());

		}
		//�폜�҂��̏�ԂɂȂ����^�X�N���폜
		void KillTask()
		{
			auto itrNewEnd = std::remove_if(taskA.begin(), taskA.end()
				, [](BTask::SP s)->bool
				{ return s->taskstate == BTask::Taskstate::Kill; });
			taskA.erase(itrNewEnd, taskA.end());
		}
		//�f�o�b�O���b�Z�[�W�E�B���h�E
		void DebugMessage(const char* text,const char* windowtext="�f�o�b�O���b�Z�[�W")
		{
			int btnid = MessageBox(NULL, text,windowtext, MB_OK);
		}
		//���y���Đ��imusiclist[����������],����(0�`255)�j//���[�v
		void PlayMusicLoop(int m_, int volume)
		{
			ChangeNextPlayVolumeSoundMem(volume, m_);

			PlaySoundMem(m_, DX_PLAYTYPE_LOOP);
		}
		//���y���Đ��imusiclist[����������],����(0�`255)�j//���[�v��Ή�
		void PlayMusicBack(int m_, int volume)
		{
			ChangeNextPlayVolumeSoundMem(volume, m_);

			PlaySoundMem(m_, DX_PLAYTYPE_BACK);
		}
		//���y���Đ��imusiclist[����������],����(0�`255)�j//�Đ��I���܂œ�����~
		void PlayMusicJingle(int m_, int volume)
		{
			ChangeNextPlayVolumeSoundMem(volume, m_);

			PlaySoundMem(m_, DX_PLAYTYPE_NORMAL);
		}
	};
	//��`�N���X
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