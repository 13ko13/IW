#include "MoveSpikeMgr.h"
#include "MoveSpike.h"
#include "Game.h"
#include "DxLib.h"

MoveSpikeMgr::MoveSpikeMgr() :
	m_graphHandle(-1)
{
}

MoveSpikeMgr::~MoveSpikeMgr()
{
}

void MoveSpikeMgr::Init(int graphHandle)
{
	m_graphHandle = graphHandle;
}

void MoveSpikeMgr::Update()
{
	for (auto& spike : m_moveSpikes)
	{
		spike.Update();
	}

	//非アクティブなとげを削除
	m_moveSpikes.erase(
		std::remove_if(m_moveSpikes.begin(), m_moveSpikes.end(),
			[](const MoveSpike& spike) { return !spike.IsActive(); }),
		m_moveSpikes.end()
	);
}

void MoveSpikeMgr::Draw()
{
	for (auto& spike : m_moveSpikes)
	{
		spike.Draw();
	}
}
