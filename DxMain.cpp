//ゲーム根幹
#include "Dxmain.h"
#include "SceneMgr.h"
#include "Task_Title.h"
#include "MyGE.h"
#include "resource.h"
//ゲーム情報
using namespace std;
constexpr int  KEY_NUM			= 256;

//関数定義*********************************************************************************
	int gpUpdateKey(char* key) {
		//現在のキーの入力状態を格納する
		char tmpKey[KEY_NUM];
		//全てのキーの入力状態を得る
		GetHitKeyStateAll(tmpKey);
		for (int i = 0; i < KEY_NUM; i++) {
			if (tmpKey[i] != 0)
			{//i番のキーコードに対応するキーが押されていたら加算
				key[i]++;
			}
			else
			{//押されていなければ0にする
				key[i] = 0;
			}
		}
		return 0;
	}
	bool Process(char* key)
	{
		if (ProcessMessage() != 0) return false;
		//画面の裏ページの内容を表ページに反映する
		if (ScreenFlip() != 0) return false;
		//画面を初期化
		if (ClearDrawScreen() != 0) return false;
		//キー取得
		if (gpUpdateKey(key) != 0) return false;
		//エスケープで終了
		if (key[KEY_INPUT_ESCAPE] >= 1) return false;
		//終了
		if (ge->GameEnd() != true)return false;
		return true;
	}
	Fps::Fps()
	{
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}
	bool Fps::Update()
	{
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}
	void Fps::Wait()
	{
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}

//**********************************************************************************************
// プログラムは WinMain から始まります
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
		//ウインドウモードに変更
		ChangeWindowMode(TRUE);
		ge = new MyGE::MyGameEngine();
		//画面サイズを代入
		ge->Resolution.x = 1920;
		ge->Resolution.y = 1080;
		//フォントサイズを変更
		SetFontSize(64);
		//ウィンドウのサイズを指定
		SetGraphMode(ge->Resolution.x,ge->Resolution.y, 32,60);
		//DXライブラリを初期化する。
		if (DxLib_Init() == -1) return -1;
		//キー取得
		char key[KEY_NUM];
		//描画先画面を裏にする
		SetDrawScreen(DX_SCREEN_BACK);
		//管理システムを動的確保
		CManager* manager;
		manager = new CManager(key);
		//タイトルを動的確保
		manager->scene = new Title::Object(manager);
		Fps fps;
		while (Process(key))
		{
			//FPSの均一化
			fps.Update();
			fps.Wait();
			//デバッグ用のタスクリストの出力
			if (manager->GetKey()[KEY_INPUT_SPACE] >= 1)
			{
				ge->WriteDebugTaskList();
			}
			//ゲームループ
			manager->Render();
			ge->TRender();
			manager->Update();
			ge->TUpDate();

			//タスクの追加・削除
			ge->AddTask();
			ge->KillTask();
		}
		//終了時にタスクリストを消す
		if (ge->deleteDebugTextList("./data/debug/tasklist.txt")) {  }
		else{}
		//後始末
		delete ge;
		delete manager;

		//DXライブラリを終了する。
		DxLib_End();

		return 0;
	}