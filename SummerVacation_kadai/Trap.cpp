#include "Trap.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kTrapSize = 16.0f; // トラップのサイズ
	constexpr float kScale = 2.0f; // トラップの拡大率
	constexpr int kRightSpikeIndex = 1; // 右向きトラップのインデックス
	constexpr int kUpSpikeIndex = 0; // 上向きトラップのインデックス
	constexpr int kLeftSpikeIndex = 3; // 左向きトラップのインデックス

}

Trap::Trap():
	m_RtrapPos({ 0.0f, 0.0f }),
	m_UtrapPos({ 0.0f, 0.0f }),
	m_LtrapPos({ 0.0f, 0.0f }),
	m_velocity({ 0.0f, 0.0f }),
	m_Rhandle(-1),
	m_Uhandle(-1),
	m_Lhandle(-1),
	m_isActive(false)
{
}

Trap::~Trap()
{
	//グラフィック削除はTrapManagerで行う
}

void Trap::Init(
	const Vec2& RtrapPos, const Vec2& UtrapPos,
	const Vec2& LtrapPos,
	const Vec2& velocity,
	int RgraphHandle, int UgraphHandle, int LgraphHandle)
{
	m_RtrapPos = RtrapPos;
	m_UtrapPos = UtrapPos;
	m_LtrapPos = LtrapPos;
	m_velocity = velocity;
	m_Rhandle = RgraphHandle;
	m_Uhandle = UgraphHandle;
	m_Lhandle = LgraphHandle;
	m_isActive = true;

	m_RtrapColRect.SetCenter(m_RtrapPos.x, m_RtrapPos.y, kTrapSize, kTrapSize);
	m_UtrapColRect.SetCenter(m_UtrapPos.x, m_UtrapPos.y, kTrapSize, kTrapSize);
	m_LtrapColRect.SetCenter(m_LtrapPos.x, m_LtrapPos.y, kTrapSize, kTrapSize);
}

void Trap::End()
{

}

void Trap::Update()
{
	if (!m_isActive) return;	//トラップがアクティブでない場合は更新しない

	m_RtrapPos += m_velocity;

	//画面外に出たら非アクティブにする
	if(m_RtrapPos.x < -kTrapSize || m_RtrapPos.x > Game::kScreenWidth ||
	   m_RtrapPos.y < -kTrapSize || m_RtrapPos.y > Game::kScreenHeight)
	{
		m_isActive = false;
		return;
	}

	m_RtrapColRect.SetCenter(m_RtrapPos.x, m_RtrapPos.y, kTrapSize, kTrapSize);
	m_UtrapColRect.SetCenter(m_UtrapPos.x, m_UtrapPos.y, kTrapSize, kTrapSize);
	m_LtrapColRect.SetCenter(m_LtrapPos.x, m_LtrapPos.y, kTrapSize, kTrapSize);
}

void Trap::Draw()
{
	if (!m_isActive) return; //トラップがアクティブでない場合は描画しない

	int RtrapSrcX = kTrapSize * kRightSpikeIndex; // 右向きトラップの切り取り位置
	int RtrapSrcY = 0;

	DrawRectRotaGraph(
		m_RtrapPos.x, m_RtrapPos.y,
		RtrapSrcX, RtrapSrcY,
		kTrapSize, kTrapSize,
		kScale, 0.0f,
		m_Rhandle,
		true
		);

	int UtrapSrcX = kTrapSize * kUpSpikeIndex; // 上向きトラップの切り取り位置
	int UtrapSrcY = 0;

	DrawRectRotaGraph(
		m_UtrapPos.x, m_UtrapPos.y,
		UtrapSrcX, UtrapSrcY,
		kTrapSize, kTrapSize,
		kScale, 0.0f,
		m_Uhandle,
		true
	);

	int LtrapSrcX = kTrapSize * kLeftSpikeIndex; // 左向きトラップの切り取り位置
	int LtrapSrcY = 0;

	DrawRectRotaGraph(
		m_LtrapPos.x, m_LtrapPos.y,
		LtrapSrcX, LtrapSrcY,
		kTrapSize, kTrapSize,
		kScale, 0.0f,
		m_Lhandle,
		true
	);
}

bool Trap::IsActive() const
{
	return m_isActive;
}

Rect Trap::GetRightRect() const
{
	return m_RtrapColRect;
}

Rect Trap::GetUpRect() const
{
	return m_UtrapColRect;
}

Rect Trap::GetLeftRect() const
{
	return m_LtrapColRect;
}