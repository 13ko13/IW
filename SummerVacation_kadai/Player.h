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
	int m_handle;	//プレイヤーのグラフィックハンドル

	Vec2 m_pos;

	bool m_isTurn;//左右反転するか

	//アニメーション関連
	int m_animFrame;	//アニメーションのフレーム数
};

