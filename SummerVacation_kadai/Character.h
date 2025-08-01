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
	Vec2 m_pos;		//À•W
	Vec2 m_move;	//ˆÚ“®
	Rect m_colRect;	//“–‚½‚è”»’è—p‚Ì‹éŒ`
};

