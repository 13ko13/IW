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
	m_colRect.SetCenter(m_pos.x, m_pos.y, kSpikeWidth, kSpikeHeight); // 当たり判定用の矩形を設定
}

void MoveSpike::Update()
{
	if (!m_isActive) return;
	// トゲの位置を更新
	if (m_pos.y < 280.0f)
	{
		m_pos += m_velocity * kSpikeSpeed; //下に動かす
	}
	else if (m_pos.y > 300.0f)
	{
		m_pos -= m_velocity * kSpikeSpeed; // 画面外に出たら元の位置に戻す
	}
	

	m_colRect.SetCenter(m_pos.x, m_pos.y, kSpikeWidth, kSpikeHeight); // 当たり判定用の矩形を更新
}

void MoveSpike::Draw()
{
	if (!m_isActive) return;
	DrawRotaGraphF(
		m_pos.x, m_pos.y,
		1.0f, 0.0f,
		m_handle, TRUE); // トゲを描画
}

bool MoveSpike::IsActive() const
{
	return m_isActive;
}

Rect MoveSpike::GetRect() const
{
	return m_colRect; // 当たり判定用の矩形を返す
}


