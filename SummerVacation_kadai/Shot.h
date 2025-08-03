#pragma once
#include "Vec2.h"

class Shot
{
public:
	Shot();
	~Shot();

	void Init(int handle);
	void Update();
	void Draw();

private:
	Vec2 m_pos;		//弾の位置
	int m_handle;	//グラフィックハンドル
};

