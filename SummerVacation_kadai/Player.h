#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	~Player();

	void Init(int handle);
	void End();
	void Update();
	void Draw();

private:
	int m_handle;	//�v���C���[�̃O���t�B�b�N�n���h��

	Vec2 m_pos;

	bool m_isTurn;//���E���]���邩

	//�A�j���[�V�����֘A
	int m_animFrame;	//�A�j���[�V�����̃t���[����
};

