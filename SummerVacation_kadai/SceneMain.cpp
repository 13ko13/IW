#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"

SceneMain::SceneMain() :
	m_tileGraphHandle(-1),
	m_bgGraphHandle(-1)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	//�O���t�B�b�N�����[�h����
	m_tileGraphHandle = LoadGraph("data/tileset.png");
	m_bgGraphHandle = LoadGraph("data/3-bg-full.png");
	m_bg.Init(m_tileGraphHandle,m_bgGraphHandle);
}

void SceneMain::End()
{
	m_bg.End();
	//�O���t�B�b�N���J��
	DeleteGraph(m_tileGraphHandle);
	DeleteGraph(m_bgGraphHandle);
}

void SceneMain::Update()
{
}

void SceneMain::Draw()
{
	m_bg.Draw();
}
