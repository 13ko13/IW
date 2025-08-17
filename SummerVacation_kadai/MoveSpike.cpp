#include "MoveSpike.h"
#include "DxLib.h"
#include "Game.h"
#include "Vec2.h"
#include "Rect.h"

namespace
{
	constexpr float kSpikeWidth = 48.0f; // トゲの幅
	constexpr float kSpikeHeight = 32.0f; // トゲの高さ
	constexpr float kSpikeSpeed = 2.0f; // トゲの移動速度
}

MoveSpike::MoveSpike() :
	m_handle(-1),
	m_isActive(false),
	m_pos({ 0.0f, 0.0f }),
	m_velocity({ 0.0f, 0.0f })
{
}

MoveSpike::~MoveSpike()
{
}

void MoveSpike::Init(const Vec2& pos, const Vec2& velocity, int graphHandle)
{
	m_handle = graphHandle;
	m_isActive = true;
	m_pos = pos;
	m_velocity = velocity;
	m_colRect.SetCenter(m_pos.x, m_pos.y, 32.0f, 32.0f); // 当たり判定用の矩形を設定
}



