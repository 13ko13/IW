#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"
#include "player.h"
#include "Trap.h"

SceneMain::SceneMain() :
	m_playerIdleGraphHandle(-1),
	m_playerWalkGraphHandle(-1),
	m_tileGraphHandle(-1),
	m_bgGraphHandle(-1)
{
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
	m_player.Init(m_playerIdleGraphHandle,m_playerIdleGraphHandle,m_playerWalkGraphHandle);
	m_bg.Init(m_tileGraphHandle,m_bgGraphHandle);
}

void SceneMain::End()
{
	m_player.End();
	m_bg.End();
	//グラフィックを開放
	DeleteGraph(m_playerIdleGraphHandle);
	DeleteGraph(m_playerWalkGraphHandle);
	DeleteGraph(m_tileGraphHandle);
	DeleteGraph(m_bgGraphHandle);
}

void SceneMain::Update()
{
	m_player.Update();
}

void SceneMain::Draw()
{
	m_bg.Draw();
	m_player.Draw();
}
