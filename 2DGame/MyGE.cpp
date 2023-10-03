//�Q�[���G���W���i�^�X�N�����⋤�L����ϐ��A�֐��j
#include "MyGE.h"
#include <sstream>
namespace MyGE
{
	//�^�X�N�̃A�b�v�f�[�g
	void MyGameEngine::TUpDate()
	{
		for (auto it = taskA.begin(); it != taskA.end(); it++)
		{
			if((*it)->taskstate==BTask::Taskstate::Normal)
			(*it)->Update();
		}
	}
	//�^�X�N�̕`��
	void MyGameEngine::TRender()
	{
		for (auto it = taskA.begin(); it != taskA.end(); it++)
		{
			if ((*it)->taskstate != BTask::Taskstate::Kill)
			(*it)->Render();
		}
	}
}
MyGE::MyGameEngine* ge;