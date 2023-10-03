//�Q�[���N���A�V�[��
#pragma once
#include "Task_GameClear.h"
namespace GameClear
{
	Object::Object(CManager* pManager) : BTask(pManager)
	{
		
		//�摜
		LoadDivGraph("./data/image/PlayerX.png", 70, 10, 7, Player_ImageX / 10, Player_ImageY / 7, graphic);
		img[0] = LoadGraph("./data/image/GameClear.png");
		img[1] = LoadGraph("./data/image/Clearlogo.png");
		img[2] = LoadGraph("./data/image/GameResult.png");
		//�A�j���[�V�����̏����l
		anim = 20;
		//�A�j���[�V�����J�E���^
		anicnt = 0;
		//�Đ�
		ge->PlayMusicBack(music, 70);
	};
	void Object::Update()
	{
		anicnt++;
		Anim();
		if (manager->GetKey()[KEY_INPUT_RETURN] > 0)
		{
			ge->gamestate = MyGE::MyGameEngine::GameState::Non;
			//�Q�[���ɃV�[���ڍs
			manager->scene = new Title::Object(manager);
			delete this;
		}
		if (anicnt>5)
		{
			anim++;
			anicnt = 0;
		}
		if (anim>34)
		{
			anim = 34;
		}
	}
	void Object::Render()
	{
		DrawGraph(0,0,img[0],FALSE);

		DrawGraph(600, 100+y, img[1], TRUE);

		DrawGraph(650, 300, img[2], TRUE);

		DrawExtendGraph(600, 420, 600 + 897, 420 + 672, graphic[anim], TRUE);
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
}