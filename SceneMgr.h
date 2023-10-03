//�V�[���̊Ǘ��}�l�[�W���[
#pragma once
#include "Dxmain.h"
class CManager;
//�V�[���̊��N���X
class BTask
{
protected:
	CManager* manager;
private:

public:
	string  GroupName;	//��ޖ� 
	string  name;       //�ŗL��
	using SP = shared_ptr<BTask>;
	enum class Taskstate
	{
		Normal,
		Kill,
		Stop
	};
	Taskstate taskstate;//�^�X�N�̏��
	int Killcnt;        //�폜�\��̃^�X�N�̃J�E���g

	BTask(CManager* pManager) { manager = pManager;};
	virtual ~BTask() {};

	//������
	bool Initialize(const  string& gn_)
	{
		this->GroupName = gn_;
		this->taskstate = Taskstate::Normal;
		this->Killcnt = 0;
		return true;
	}
	//�j��
	virtual void Dead() {};
	//�`��
	virtual void Update() {};
	//�X�V
	virtual void Render() {};
	//��~
	void Stop(bool  f_ = true)
	{
		if (f_) { this->taskstate = BTask::Taskstate::Stop; }
		else { this->taskstate = BTask::Taskstate::Normal; }
	}
};
//�V�[���Ǘ��N���X
class CManager
{

public:
	//�L�[
	char* key;
	//���̃V�[���̃|�C���^
	BTask* scene=nullptr;

	CManager(char* pKey) { key = pKey; };
	~CManager() { delete scene; };
	char* GetKey() { return key; }
	//�`��
	void Update() { scene->Update();};
	//�X�V
	void Render() { scene->Render(); };
};