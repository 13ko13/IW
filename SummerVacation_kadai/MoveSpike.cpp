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
	//printfDx("%d", m_isActive);
	if (!m_isActive) return; // トゲがアクティブでない場合は更新しない

	if (m_pos.y < 250.0f ) // トゲの位置を更新
	{
		printfDx("a");
		m_pos += m_velocity * kSpikeSpeed;
	}
	else if (m_pos.y > 250.0f )
	{
		for (int y = 0; y < 250; y++)
		{
			m_pos.y -= m_velocity.y * kSpikeSpeed; // 位置を戻す
		}		
	}

	// 当たり判定用の矩形を更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kSpikeWidth, kSpikeHeight);
}

void MoveSpike::Draw()
{
	//if (!m_isActive) return; // トゲがアクティブでない場合は描画しない
	// トゲの描画
	DrawRotaGraph(
		static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y),
		1.0f, 0.0f,
		m_handle, true);
}

bool MoveSpike::IsActive() const
{
	return m_isActive;
}

Rect MoveSpike::GetRect() const
{
	return m_colRect; // 当たり判定用の矩形を返す
}