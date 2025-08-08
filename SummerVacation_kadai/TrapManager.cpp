#include "TrapManager.h"

TrapManager::TrapManager() :
	m_trapGraphHandle(-1)
{
}

TrapManager::~TrapManager()
{
	//Trap�̃O���t�B�b�N��DxLib�ŊǗ�����Ă��邽�߁A�����ł͍폜���Ȃ�o
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

	//��A�N�e�B�u�ȃg�Q���폜
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
	m_traps.push_back(newTrap); // �g���b�v�����X�g�ɒǉ�
}

bool TrapManager::CheckCollision(const Rect& playerRect)
{
	for (auto& trap : m_traps)
	{
		if (trap.IsActive() && trap.GetRect().IsCollision(playerRect))
		{
			return true; // �v���C���[�ƃg���b�v���Փ�
		}
	}
	return false; // �Փ˂Ȃ�
}


