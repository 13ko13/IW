#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"
#include "player.h"
#include "Trap.h"
#include "Shot.h"
#include "Game.h"

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
	m_bulletGraphHandle(-1)
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
	m_pPlayer->Init(m_playerIdleGraphHandle, m_playerIdleGraphHandle, m_playerWalkGraphHandle, m_playerShotGraphHnadle,m_playerJumpGraphHandle,m_playerDJumpGraphHandle);
	m_pBg->Init();
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
	/*for(int i = 0; i < kShotMax; i ++)
	{
		if (m_pShot[i])
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}*/
}

void SceneMain::Update()
{

	m_pPlayer->Update();

	if (!m_pShot) return;
	//for (int i = 0; i < kShotMax; i++)
	//{
	//	if (!m_pShot) continue;
	//	m_pShot[i]->Update();
	//}

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
