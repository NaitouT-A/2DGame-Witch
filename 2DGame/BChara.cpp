//キャラクタクラス
#include "BChara.h"
bool BChara::updateMotion(Motion nm_)
{
	if (nm_==this->motion)
	{
		return false;
	}
	else
	{
		this->motion = nm_;
		this->moveCnt = 0;
		this->AnimTime = 0;
		return true;
	}
}