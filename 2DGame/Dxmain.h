//ÉQÅ[ÉÄç™ä≤
#pragma once
#include "iomanip"
#include "DxLib.h"
#include "fstream"
#include "sstream"
#include "iostream"
#include "conio.h"
#include "string"
constexpr int  SCREEN_HEIGHT = 1980;
constexpr int  SCREEN_WIDTH = 1080;

using namespace std;

class Fps {
	int mStartTime;        
	int mCount;             
	float mFps;            
	static const int N = 60;
	static const int FPS = 60;	

public:
	Fps();

	bool Update(); 

	void Wait();
};

