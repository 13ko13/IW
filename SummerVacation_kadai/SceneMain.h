#pragma once
#include "Bg.h"
#include "Player.h"
#include "Shot.h"
#include "TrapManager.h"
#include "PlatformManager.h"

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
	int m_RtrapGraphHandle;			//右向きトラップのグラフィック
	int m_UtrapGraphHandle;		//上向きトラップのグラフィック
	int m_platformGraphHandle;		//プラットフォームのグラフィック
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	int m_moveSpikeGraphHandle;		//移動とげのグラフィック
=======
	int m_
>>>>>>> Stashed changes
=======
	int m_
>>>>>>> Stashed changes

	//トゲ発射済みフラグ
	bool m_isRtrapFired;
	//プラットフォームフラグ
	bool m_isPlatformSpawned;	//一度だけ生成するフラグ
	//トゲ設置済みフラグ
	bool m_isUtrapSpawned;	//一度だけ生成するフラグ(下向きトゲ)

	//プレイヤー
	Player* m_pPlayer;
	//背景
	Bg* m_pBg;
	//弾
	Shot* m_pShot[5];
	//トラップマネージャー
	TrapManager m_trapManager;
	//プラットフォームマネージャー
	PlatformManager m_platformManager;
	//移動とげマネージャー
};