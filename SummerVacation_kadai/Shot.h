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
	int m_handle;	//グラフィックハンドル

	Vec2 m_pos;		//弾の位置
	Vec2 m_move;	//移動量
};

