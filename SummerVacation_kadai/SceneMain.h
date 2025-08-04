#pragma once
#include "Bg.h"
#include "Player.h"
#include "Shot.h"

class Player;
class Shot;

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
	void UpdateShot();

private:
	//使用するグラフィック
	int m_playerIdleGraphHandle;	//プレイヤーのアイドルグラフィック
	int m_playerWalkGraphHandle;	//プレイヤーの歩きグラフィック
	int m_tileGraphHandle;	//マップチップのグラフィック
	int m_bgGraphHandle;	//背景のグラフィック
	int m_shotGraphHandle;	//弾のグラフィック

	//プレイヤー
	Player* m_pPlayer;
	//背景
	Bg m_bg;
	//弾
	Shot* m_pShot;
};

