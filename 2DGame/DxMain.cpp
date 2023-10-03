//�Q�[������
#include "Dxmain.h"
#include "SceneMgr.h"
#include "Task_Title.h"
#include "MyGE.h"
#include "resource.h"
//�Q�[�����
using namespace std;
constexpr int  KEY_NUM			= 256;

//�֐���`*********************************************************************************
	int gpUpdateKey(char* key) {
		//���݂̃L�[�̓��͏�Ԃ��i�[����
		char tmpKey[KEY_NUM];
		//�S�ẴL�[�̓��͏�Ԃ𓾂�
		GetHitKeyStateAll(tmpKey);
		for (int i = 0; i < KEY_NUM; i++) {
			if (tmpKey[i] != 0)
			{//i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�������Z
				key[i]++;
			}
			else
			{//������Ă��Ȃ����0�ɂ���
				key[i] = 0;
			}
		}
		return 0;
	}
	bool Process(char* key)
	{
		if (ProcessMessage() != 0) return false;
		//��ʂ̗��y�[�W�̓��e��\�y�[�W�ɔ��f����
		if (ScreenFlip() != 0) return false;
		//��ʂ�������
		if (ClearDrawScreen() != 0) return false;
		//�L�[�擾
		if (gpUpdateKey(key) != 0) return false;
		//�G�X�P�[�v�ŏI��
		if (key[KEY_INPUT_ESCAPE] >= 1) return false;
		//�I��
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
		if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
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
		int tookTime = GetNowCount() - mStartTime;	//������������
		int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}

//**********************************************************************************************
// �v���O������ WinMain ����n�܂�܂�
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
		//�E�C���h�E���[�h�ɕύX
		ChangeWindowMode(TRUE);
		ge = new MyGE::MyGameEngine();
		//��ʃT�C�Y����
		ge->Resolution.x = 1920;
		ge->Resolution.y = 1080;
		//�t�H���g�T�C�Y��ύX
		SetFontSize(64);
		//�E�B���h�E�̃T�C�Y���w��
		SetGraphMode(ge->Resolution.x,ge->Resolution.y, 32,60);
		//DX���C�u����������������B
		if (DxLib_Init() == -1) return -1;
		//�L�[�擾
		char key[KEY_NUM];
		//�`����ʂ𗠂ɂ���
		SetDrawScreen(DX_SCREEN_BACK);
		//�Ǘ��V�X�e���𓮓I�m��
		CManager* manager;
		manager = new CManager(key);
		//�^�C�g���𓮓I�m��
		manager->scene = new Title::Object(manager);
		Fps fps;
		while (Process(key))
		{
			//FPS�̋ψꉻ
			fps.Update();
			fps.Wait();
			//�f�o�b�O�p�̃^�X�N���X�g�̏o��
			if (manager->GetKey()[KEY_INPUT_SPACE] >= 1)
			{
				ge->WriteDebugTaskList();
			}
			//�Q�[�����[�v
			manager->Render();
			ge->TRender();
			manager->Update();
			ge->TUpDate();

			//�^�X�N�̒ǉ��E�폜
			ge->AddTask();
			ge->KillTask();
		}
		//�I�����Ƀ^�X�N���X�g������
		if (ge->deleteDebugTextList("./data/debug/tasklist.txt")) {  }
		else{}
		//��n��
		delete ge;
		delete manager;

		//DX���C�u�������I������B
		DxLib_End();

		return 0;
	}