#pragma once
#include "Bg.h"
#include "Player.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	//使用するグラフィック
	int m_playerIdleGraphHandle;	//プレイヤーのアイドルグラフィック
	int m_playerWalkGraphHandle;	//プレイヤーの歩きグラフィック
	int m_tileGraphHandle;	//マップチップのグラフィック
	int m_bgGraphHandle;	//背景のグラフィック

	//プレイヤー
	Player m_player;
	//背景
	Bg m_bg;
};

