#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"
#include "player.h"
#include "Trap.h"
#include "Shot.h"
#include "Game.h"
#include "TrapManager.h"

namespace
{
	constexpr int kShotMax = 5;	//1度に撃てる最大弾数
}

SceneMain::SceneMain() :
	m_playerIdleGraphHandle(-1),
	m_playerWalkGraphHandle(-1),
	m_playerShotGraphHnadle(-1),
	m_playerJumpGraphHandle(-1),
	m_playerDJumpGraphHandle(-1),
	m_tileGraphHandle(-1),
	m_bgGraphHandle(-1),
	m_bulletGraphHandle(-1),
	m_RtrapGraphHandle(-1),
	m_UtrapGraphHandle(-1),
	m_platformGraphHandle(-1),
	m_isRtrapFired(false),
	m_isPlatformSpawned(false),
	m_isUtrapSpawned(false)
	//m_pShot(nullptr)
{
	m_pPlayer = new Player;
	for (int i = 0; i < kShotMax; i++)
	{
		m_pShot[i] = nullptr;
	}

	m_pBg = new Bg;
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	//グラフィックをロードする
	m_playerIdleGraphHandle = LoadGraph("data/idle.png");
	m_playerWalkGraphHandle = LoadGraph("data/Run.png");
	m_playerShotGraphHnadle = LoadGraph("data/Shoot.png");
	m_playerJumpGraphHandle = LoadGraph("data/Jump.png");
	m_playerDJumpGraphHandle = LoadGraph("data/Jump.png");
	m_tileGraphHandle = LoadGraph("data/tileset.png");
	m_bgGraphHandle = LoadGraph("data/3-bg-full.png");
	m_RtrapGraphHandle = LoadGraph("data/SpikeTrap.png");
	m_UtrapGraphHandle = LoadGraph("data/SpikeTrap.png");
	m_platformGraphHandle = LoadGraph("data/fakeTileset.png");

	m_pPlayer->Init(m_playerIdleGraphHandle, m_playerIdleGraphHandle, m_playerWalkGraphHandle, m_playerShotGraphHnadle, m_playerJumpGraphHandle, m_playerDJumpGraphHandle);
	m_pBg->Init();
	m_trapManager.Init(m_RtrapGraphHandle,m_UtrapGraphHandle);
	m_platformManager.Init(m_platformGraphHandle);
	m_pPlayer->SetPlatformManager(&m_platformManager);
	/*for (int i = 0; i < kShotMax; i++)
	{
		m_pShot[i]->Init();
	}*/
}

void SceneMain::End()
{
	m_pPlayer->End();
	m_pBg->End();
	//グラフィックを開放
	DeleteGraph(m_playerIdleGraphHandle);
	DeleteGraph(m_playerWalkGraphHandle);
	DeleteGraph(m_playerShotGraphHnadle);
	DeleteGraph(m_playerJumpGraphHandle);
	DeleteGraph(m_playerDJumpGraphHandle);
	DeleteGraph(m_tileGraphHandle);
	DeleteGraph(m_bgGraphHandle);
	DeleteGraph(m_bulletGraphHandle);
	DeleteGraph(m_RtrapGraphHandle);
	DeleteGraph(m_UtrapGraphHandle);
	DeleteGraph(m_platformGraphHandle);
}

void SceneMain::Update()
{

	m_pPlayer->Update();
	m_trapManager.Update();
	m_platformManager.Update(m_pPlayer->GetColRect());

	//トゲ発射イベント(X:1000,Y:300を越えたら)
	if (m_pPlayer->GetPos().x > 1100.0f && m_pPlayer->GetPos().y > 200.0f && !m_isRtrapFired)
	{
		m_trapManager.SpawnTrap({ 0.0f, 300.0f }, { -60.0f,0.0f }, { 40.0f, 0.0f }); //右に飛ぶトゲ
		m_trapManager.SpawnTrap({ 0.0f, 280.0f }, { -60.0f,0.0f }, { 40.0f, 0.0f }); //右に飛ぶトゲ
		m_isRtrapFired = true; // トゲを発射済みフラグを立てる
	}

	//トゲを設置
	if (m_pPlayer->GetPos().x > 0.0f && !m_isUtrapSpawned)
	{
		m_trapManager.SpawnTrap({ -10.0f, -0.0f }, { 848.0f, 304.0f }, { 0.0f, 0.0f }); // 上向きトゲ
		m_isUtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//プレイヤーとの当たり判定
	if (m_trapManager.CheckCollision(m_pPlayer->GetColRect()))
	{
		//プレイヤーがトゲに当たった場合の処理
		printfDx("トゲに当たった！\n");
	}

	//プラットフォーム生成イベント(X:0を越えたら)
	if (m_pPlayer->GetPos().x > 0.0f && !m_isPlatformSpawned)
	{
		//プラットフォームを生成
		m_platformManager.SpawnPlatform({ 736.0f, 168.0f }, 10.0f); // 60フレーム後に落下開始
		m_isPlatformSpawned = true; // プラットフォームを生成済みフラグを立てる
	}


	if (!m_pShot) return;

	UpdateShot();
}

void SceneMain::Draw()
{
	m_pBg->Draw();
	m_pPlayer->Draw();
	if (!m_pShot) return;
	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i]) continue;
		m_pShot[i]->Draw();
	}

	m_trapManager.Draw();
	m_platformManager.Draw();
}

void SceneMain::UpdateShot()
{
	Shot* newShot = nullptr;
	if (m_pPlayer)
	{
		newShot = m_pPlayer->CreateShot();
	}
	if (newShot != nullptr)
	{
		for (int i = 0; i < kShotMax; i++)
		{
			if (m_pShot[i] == nullptr)
			{
				m_pShot[i] = newShot;
				break;
			}
		}
	}

	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		// 画面外に出た場合
		bool isOffScreen = m_pShot[i]->GetPos().x < 0 || m_pShot[i]->GetPos().x > Game::kScreenWidth;
		if (isOffScreen) DeleteShot(i);
	}
}

void SceneMain::DeleteShot(int index)
{
	if (!m_pShot[index]) return;

	delete m_pShot[index];
	m_pShot[index] = nullptr;
}
