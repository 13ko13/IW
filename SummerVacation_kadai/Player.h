#pragma once
#include "Vec2.h"
#include "Character.h"
#include "Shot.h"

class Player : public Character
{
public:
	Player();
	virtual ~Player();

	virtual void Init(int handle,int handleRun, int handleWalk);
	void End();
	virtual void Update() override;
	virtual void Draw()override;
	Shot* CreateShot();

private:
	//�ړ�
	void Move();
	//�W�����v
	void Jump();

	//Vec2 m_pos;
	
	//�v���C���[�����͏�Ԃ��ǂ����̃t���O
	bool m_isInput;

	//�A�j���[�V�����֘A
	int m_animFrame;	//�A�j���[�V�����̃t���[����


};

