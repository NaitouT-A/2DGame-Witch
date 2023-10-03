//ゲームエンジン（タスク処理や共有する変数、関数）
#include "MyGE.h"
#include <sstream>
namespace MyGE
{
	//タスクのアップデート
	void MyGameEngine::TUpDate()
	{
		for (auto it = taskA.begin(); it != taskA.end(); it++)
		{
			if((*it)->taskstate==BTask::Taskstate::Normal)
			(*it)->Update();
		}
	}
	//タスクの描画
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