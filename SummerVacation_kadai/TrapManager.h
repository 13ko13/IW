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

	void SpawnTrap(const Vec2& pos, const Vec2& velocity);	// トラップを生成
	bool CheckCollision(const Rect& playerRect);			// プレイヤーとの衝突判定

private:
	std::vector<Trap> m_traps;	// トラップのリスト
	int m_trapGraphHandle;	// トラップのグラフィックハンドル
};

