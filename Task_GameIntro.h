#pragma once
#include "BChara.h"
#include "Task_Game.h"
#include "Task_Game2.h"
class CManager;
namespace GameIntro {
	class Object :public BTask
	{
		CManager* manager;
		//�摜�f�[�^�i�[
		int graphic[2];

		int cnt;
		int mx, my;
		int mouse;
	public:
		//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
		Object(CManager* pManager) :BTask(pManager)
		{
			manager = pManager;
			//�摜�f�[�^�i�[
			graphic[0] = LoadGraph("./data/image/���[�h���.png");

			graphic[1] = LoadGraph("./data/image/StartButton.png");
			cnt = 0;
		};
		//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
		~Object() {};
		//�`��̍X�V
		void Render();
		//�X�V
		void Update();
	};
}