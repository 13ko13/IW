#pragma once
#include "Vec2.h"

class Shot
{
public:
	Shot();
	~Shot();

	void Init();
	void Update();
	void Draw();

	void SetInfo(const Vec2& pos, bool isTurn);

private:
	int m_handle;	//�O���t�B�b�N�n���h��

	Vec2 m_pos;		//�e�̈ʒu
	Vec2 m_move;	//�ړ���
};

