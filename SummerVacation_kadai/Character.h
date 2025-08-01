#pragma once
#include "Rect.h"
#include "Vec2.h"

class Character
{
public:
	Character();
	~Character();

	void Init();
	void Update();
	void Draw();

protected:
	Vec2 m_pos;		//���W
	Vec2 m_move;	//�ړ�
	Rect m_colRect;	//�����蔻��p�̋�`
};

