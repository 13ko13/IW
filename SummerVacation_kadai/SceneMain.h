#pragma once
#include "Bg.h"
#include "Player.h"
#include "Shot.h"
#include "TrapManager.h"

class Player;
class Shot;
class Bg;

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
	void UpdateShot(); //弾更新
	void DeleteShot(int index); //弾削除

private:
	//使用するグラフィック
	int m_playerIdleGraphHandle;	//プレイヤーのアイドルグラフィック
	int m_playerWalkGraphHandle;	//プレイヤーの歩きグラフィック
	int m_playerShotGraphHnadle;	//プレイヤーの弾撃ちグラフィック
	int m_playerJumpGraphHandle;	//プレイヤーのジャンプグラフィック
	int m_playerDJumpGraphHandle;	//プレイヤーの二段ジャンプグラフィック
	int m_tileGraphHandle;			//マップチップのグラフィック
	int m_bgGraphHandle;			//背景のグラフィック
	int m_bulletGraphHandle;			//弾のグラフィック
	int m_trapGraphHandle;			//トラップのグラフィック

	//トゲ発射済みフラグ
	bool m_isTrapFired = false;

	//プレイヤー
	Player* m_pPlayer;
	//背景
	Bg* m_pBg;
	//弾
	Shot* m_pShot[5];
	//トラップマネージャー
	TrapManager m_trapManager;
};

