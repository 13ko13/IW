#pragma once
#include "Vec2.h"

class player
{
public:
	player();
	~player();

	void Init(int handle);
	void End();
	void Update();
	void Draw();

private:
	int m_handle;	//プレイヤーのグラフィックハンドル

	Vec2 m_pos;
};

