#include "TrapManager.h"

TrapManager::TrapManager() :
	m_trapGraphHandle(-1)
{
}

TrapManager::~TrapManager()
{
	//TrapのグラフィックはDxLibで管理されているため、ここでは削除しないo
}

void TrapManager::Init(int trapGraphHandle)
{
	m_trapGraphHandle = trapGraphHandle;
}

void TrapManager::Update()
{
	for (auto& trap : m_traps)
	{
		trap.Update();
	}

	//非アクティブなトゲを削除
	m_traps.erase(
		std::remove_if(m_traps.begin(), m_traps.end(),
		[](const Trap& trap) { return !trap.IsActive(); }),
		m_traps.end());
}

void TrapManager::Draw()
{
	for (auto& trap : m_traps)
	{
		trap.Draw();
	}
}

void TrapManager::SpawnTrap(const Vec2& pos, const Vec2& velocity)
{
	Trap newTrap;
	newTrap.Init(pos, velocity, m_trapGraphHandle);
	m_traps.push_back(newTrap); // トラップをリストに追加
}

bool TrapManager::CheckCollision(const Rect& playerRect)
{
	for (auto& trap : m_traps)
	{
		if (trap.IsActive() && trap.GetRect().IsCollision(playerRect))
		{
			return true; // プレイヤーとトラップが衝突
		}
	}
	return false; // 衝突なし
}


