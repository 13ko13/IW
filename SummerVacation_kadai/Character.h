#pragma once
#include "Rect.h"
#include "Vec2.h"

class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//�v���C���[�̌��݂̍s��
	enum class PlayerState
	{
		Idle,
		Walk,
		Shot
	};

	PlayerState m_state;

protected:	
	void Gravity();

protected:
	int m_handle;
	//�v���C���[�̓��͑ҋ@���̃O���t�B�b�N�n���h��
	int m_handleIdle;
	//�v���C���[�̕������͒��̃O���t�B�b�N�n���h��
	int m_handleWalk;
	//�v���C���[�̒e�������͒��̃O���t�B�b�N�n���h��
	int m_handleShot;

	//���E���]���邩
	bool m_isTurn;
	//�n�ʂɒ��n���Ă��邩
	bool m_isGround;

	Vec2 m_pos;		//���W
	Vec2 m_move;	//�ړ�
	Rect m_colRect;	//�����蔻��p�̋�`
};