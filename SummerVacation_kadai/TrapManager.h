#pragma once

#include <vector>
#include "Trap.h"
#include "Player.h"
class TrapManager
{
public:
	TrapManager();
	~TrapManager();

	void Init(
		int RtrapGraphHandle,
		int UtrapGraphHandle,
		int LtrapGraphHandle);
	void Update();
	void Draw();

	void SpawnTrap(
		const Vec2& RtrapPos,
		const Vec2& UtrapPos,
		const Vec2& LtrapPos,
		const Vec2& velocity);	// トラップを生成
	bool CheckCollision(const Rect& playerRect);			// プレイヤーとの衝突判定

private:
	std::vector<Trap> m_Rtraps;	// 右向きトラップのリスト
	std::vector<Trap> m_Utraps;	// 上向きトラップのリスト
	std::vector<Trap> m_Ltraps;	// 左向きトラップのリスト
	int m_RtrapGraphHandle;	// 右向きトラップのグラフィックハンドル
	int m_UtrapGraphHandle;	// 上向きトラップのグラフィックハンドル
	int m_LtrapGraphHandle;	// 左向きトラップのグラフィックハンドル
};

