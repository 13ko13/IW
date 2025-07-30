#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"
#include "player.h"
#include "Trap.h"

SceneMain::SceneMain() :
	m_playerGraphHandle(-1),
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
	m_playerGraphHandle = LoadGraph("data/Idle.png");
	m_tileGraphHandle = LoadGraph("data/tileset.png");
	m_bgGraphHandle = LoadGraph("data/3-bg-full.png");
	m_player.Init(m_playerGraphHandle);
	m_bg.Init(m_tileGraphHandle,m_bgGraphHandle);
}

void SceneMain::End()
{
	m_player.End();
	m_bg.End();
	//グラフィックを開放
	DeleteGraph(m_playerGraphHandle);
	DeleteGraph(m_tileGraphHandle);
	DeleteGraph(m_bgGraphHandle);
}

void SceneMain::Update()
{
	m_player.Update();
}

void SceneMain::Draw()
{
	m_player.Draw();
	m_bg.Draw();
}
