#include "Trap.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kTrapSize = 16.0f; // トラップのサイズ
	constexpr float kScale = 2.0f; // トラップの拡大率
	constexpr int kRightSpikeIndex = 1; // 右向きトラップのインデックス
}

Trap::Trap():
	m_pos({ 0.0f, 0.0f }),
	m_velocity({ 0.0f, 0.0f }),
	m_handle(-1),
	m_isActive(false)
{
}

Trap::~Trap()
{
	//グラフィック削除はTrapManagerで行う
}

void Trap::Init(const Vec2& pos, const Vec2& velocity, int graphHandle)
{
	m_pos = pos;
	m_velocity = velocity;
	m_handle = graphHandle;
	m_isActive = true;

	m_colRect.SetCenter(m_pos.x, m_pos.y, kTrapSize, kTrapSize);
}

void Trap::End()
{

}

void Trap::Update()
{
	if (!m_isActive) return;	//トラップがアクティブでない場合は更新しない

	m_pos += m_velocity;

	//画面外に出たら非アクティブにする
	if(m_pos.x < -kTrapSize || m_pos.x > Game::kScreenWidth ||
	   m_pos.y < -kTrapSize || m_pos.y > Game::kScreenHeight)
	{
		m_isActive = false;
		return;
	}

	m_colRect.SetCenter(m_pos.x, m_pos.y, kTrapSize, kTrapSize);
}

void Trap::Draw()
{
	if (!m_isActive) return; //トラップがアクティブでない場合は描画しない

	int srcX = kTrapSize * kRightSpikeIndex; // 右向きトラップの切り取り位置
	int srcY = 0;

	DrawRectRotaGraph(
		m_pos.x, m_pos.y,
		srcX, srcY,
		kTrapSize, kTrapSize,
		kScale, 0.0f,
		m_handle,
		true
	);
}

bool Trap::IsActive() const
{
	return m_isActive;
}

Rect Trap::GetRect() const
{
	return m_colRect;
}