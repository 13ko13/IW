#pragma once
#include "Vec2.h"
#include "Character.h"
#include "Shot.h"

class Shot;

class Player : public Character
{
public:
	Player();
	virtual ~Player();

	virtual void Init(int handle,int handleRun, int handleWalk,int handleShot) ;
	void End();
	virtual void Update() override;
	virtual void Draw()override;
	Shot* CreateShot();

private:
	//�ړ�
	void Move();
	//�W�����v
	void Jump();
	//�e�̃N�[���^�C��
	void ShotCT(); 

private:
	//�����ꂽ�u�Ԃ������Ƃ邽�߂̑O��̓��͏��
	int prevInput = 0;

	//�v���C���[�����͏�Ԃ��ǂ����̃t���O
	bool m_isInput;
	//�v���C���[���e�𔭎˂��Ă����Ԃ��ǂ����̃t���O
	bool m_isShotInput;

	//�A�j���[�V�����֘A
	int m_animFrame;	//�A�j���[�V�����̃t���[����
	int m_shotAnimTime; //Shot��Ԃ��ێ����邽�߂̎��ԃJ�E���g

	//���Ԋ֘A
	int m_time;	//���Ԃ��v��
};