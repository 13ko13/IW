#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"
#include "player.h"
#include "Trap.h"
#include "Shot.h"

SceneMain::SceneMain() :
	m_playerIdleGraphHandle(-1),
	m_playerWalkGraphHandle(-1),
	m_tileGraphHandle(-1),
	m_bgGraphHandle(-1),
	m_shotGraphHandle(-1),
	m_pShot(nullptr)
{
	m_pPlayer = new Player;
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	//グラフィックをロードする
	m_playerIdleGraphHandle = LoadGraph("data/idle.png");
	m_playerWalkGraphHandle = LoadGraph("data/Run.png");
	m_tileGraphHandle = LoadGraph("data/tileset.png");
	m_bgGraphHandle = LoadGraph("data/3-bg-full.png");
	m_pPlayer->Init(m_playerIdleGraphHandle,m_playerIdleGraphHandle,m_playerWalkGraphHandle);
	m_bg.Init(m_tileGraphHandle,m_bgGraphHandle);
	m_pShot->Init();
}

void SceneMain::End()
{
	m_pPlayer->End();
	m_bg.End();
	//グラフィックを開放
	DeleteGraph(m_playerIdleGraphHandle);
	DeleteGraph(m_playerWalkGraphHandle);
	DeleteGraph(m_tileGraphHandle);
	DeleteGraph(m_bgGraphHandle);
	DeleteGraph(m_shotGraphHandle);
	if (m_pShot)
	{
		delete m_pShot;
		m_pShot = nullptr;
	}
}

void SceneMain::Update()
{

	m_pPlayer->Update();
	if (m_pShot)
	{
		m_pShot->Update();
	}
	UpdateShot();
}

void SceneMain::Draw()
{
	m_bg.Draw();
	m_pPlayer->Draw();
	if (!m_pShot) return;
	m_pShot->Draw();
}

void SceneMain::UpdateShot()
{
	Shot* newShot = m_pPlayer->CreateShot();
	if (newShot != nullptr)
	{
		m_pShot = newShot;	//弾を保持
	}

	if (!m_pShot) return;
	m_pShot->Update();
}
