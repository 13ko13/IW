#pragma once
#include "DxLib.h"
#include <vector>
#include  "Player.h"
#include "MoveSpike.h"

class MoveSpikeMgr
{
public:
	MoveSpikeMgr();
	~MoveSpikeMgr();

	void Init(int graphHandle);
	void Update();
	void Draw();

	void SpawnSpike(const Vec2& spikePos, const Vec2& velocity);
	bool CheckCollision(const Rect& playerRect);

private:
	//リスト
	std::vector<MoveSpike> m_moveSpikes;	//移動トゲリスト作成

	//グラフ関係
	int m_graphHandle;
};

