#pragma once

#include <vector>
#include "Trap.h"
#include "Player.h"
class TrapManager
{
public:
	TrapManager();
	~TrapManager();

	void Init(int trapGraphHandle);
	void Update();
	void Draw();

	void SpawnTrap(const Vec2& pos, const Vec2& velocity);	// �g���b�v�𐶐�
	bool CheckCollision(const Rect& playerRect);			// �v���C���[�Ƃ̏Փ˔���

private:
	std::vector<Trap> m_traps;	// �g���b�v�̃��X�g
	int m_trapGraphHandle;	// �g���b�v�̃O���t�B�b�N�n���h��
};

