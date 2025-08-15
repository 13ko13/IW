#include "TrapManager.h"
#include "PlatformManager.h"
#include "DxLib.h"

TrapManager::TrapManager() :
	m_RtrapGraphHandle(-1),
	m_UtrapGraphHandle(-1)
{
}

TrapManager::~TrapManager()
{
	//TrapのグラフィックはDxLibで管理されているため、ここでは削除しないo
}

void TrapManager::Init(int RtrapGraphHandle, int UtrapGraphHandle)
{
	m_RtrapGraphHandle = RtrapGraphHandle;
	m_UtrapGraphHandle = UtrapGraphHandle;
}

void TrapManager::Update()
{
	for (auto& trap : m_Rtraps)
	{
		trap.Update();
	}

	for(auto& Rtrap : m_Utraps)
	{
		Rtrap.Update();
	}

	//非アクティブなトゲを削除
	m_Rtraps.erase(
		std::remove_if(m_Rtraps.begin(), m_Rtraps.end(),
		[](const Trap& Rtrap) { return !Rtrap.IsActive(); }),
		m_Rtraps.end());
}

void TrapManager::Draw()
{
	for (auto& Rtrap : m_Rtraps)
	{
		Rtrap.Draw();
	}

	for(auto& Utrap : m_Utraps)
	{
		Utrap.Draw();
	}
}

void TrapManager::SpawnTrap(const Vec2& RtrapPos, const Vec2& UtrapPos, const Vec2& velocity)
{
	Trap newTrap;
	newTrap.Init(RtrapPos,UtrapPos, velocity, m_RtrapGraphHandle,m_UtrapGraphHandle);
	m_Rtraps.push_back(newTrap); // トラップをリストに追加
	m_Utraps.push_back(newTrap); // 上向きトラップも同様に追加
}

bool TrapManager::CheckCollision(const Rect& playerRect)
{
	for (auto& trap : m_Rtraps)
	{
		if (trap.IsActive() && trap.GetRect().IsCollision(playerRect))
		{
			return true; // プレイヤーとトラップが衝突
		}
	}

	for (auto& trap : m_Utraps)
	{
		if (trap.IsActive() && trap.GetRect().IsCollision(playerRect))
		{
			return true; // プレイヤーとトラップが衝突
		}
	}
	return false; // 衝突なし
}


