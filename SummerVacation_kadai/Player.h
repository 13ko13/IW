#pragma once
#include "Vec2.h"
#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	void Init(int handle,int handleRun, int handleWalk);
	void End();
	void Update();
	void Draw();

private:
	//�v���C���[�̌��݂̍s��
	enum class PlayerState
	{
		Idle,
		Walk
	};

private:
	//�ړ�
	void Move();

	//�v���C���[�̊�ՃO���t�B�b�N�n���h��
	int m_handle;
	//�v���C���[�̓��͑ҋ@���̃O���t�B�b�N�n���h��
	int m_handleIdle;	
	//�v���C���[�̕������͒��̃O���t�B�b�N�n���h��
	int m_handleWalk;

	Vec2 m_pos;

	//���E���]���邩
	bool m_isTurn;
	//�v���C���[�����͏�Ԃ��ǂ����̃t���O
	bool m_isInput;

	//�A�j���[�V�����֘A
	int m_animFrame;	//�A�j���[�V�����̃t���[����

	PlayerState m_state;
};

