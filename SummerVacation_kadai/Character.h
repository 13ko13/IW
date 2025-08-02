#pragma once
#include "Rect.h"
#include "Vec2.h"

class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();
	virtual  void Update();
	virtual void Draw();

protected:
	Vec2 m_pos;		//���W
	Vec2 m_move;	//�ړ�
	Rect m_colRect;	//�����蔻��p�̋�`
};

