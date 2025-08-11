#include "FallPlatTrap.h"
#include "DxLib.h"
#include "PlatformManager.h"

namespace
{
	constexpr float kPlatformWidth = 64.0f; // プラットフォームの幅
	constexpr float kPlatformHeight = 16.0f; // プラットフォームの高さ
}

FallPlatTrap::FallPlatTrap() :
	m_pos({ 0.0f, 0.0f }),
	m_delayFrames(0),
	m_currentFrames(0),
	m_handle(-1),
	m_isActive(false),
	m_playerOnPlatform(false)
{
}

FallPlatTrap::~FallPlatTrap()
{
	// グラフィック削除はDxLibで行うため、ここでは何もしない
}

void FallPlatTrap::Init(const Vec2& pos, int delayFrames, int graphHandle)
{
	m_pos = pos;
	m_delayFrames = delayFrames;
	m_currentFrames = 0;
	m_handle = graphHandle;
	m_isActive = true;

	// 当たり判定用の矩形を設定
	m_colRect.SetCenter(m_pos.x, m_pos.y, kPlatformWidth, kPlatformHeight);
}

void FallPlatTrap::Update(const Rect& playerRect)
{
	if (!m_isActive) return; // トラップがアクティブでない場合は更新しない

	// プレイヤーがプラットフォーム上にいるかどうかをチェック
	m_playerOnPlatform = m_colRect.IsCollision(playerRect);

	if (m_playerOnPlatform)
	{
		// プレイヤーがプラットフォーム上にいる場合、フレームをカウント
		m_currentFrames++;
		if (m_currentFrames >= m_delayFrames)
		{
			// 指定されたフレーム数経過後、トラップを非アクティブにする
			m_isActive = false;
		}
	}
	else
	{
		m_currentFrames = 0; // プレイヤーがいない場合はカウントをリセット
	}
	// 当たり判定用の矩形を更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kPlatformWidth, kPlatformHeight);
}

void FallPlatTrap::Draw()
{
	if (!m_isActive) return; // トラップがアクティブでない場合は描画しない

	// プラットフォームの描画
	DrawBox(
		m_pos.x - kPlatformWidth / 2,
		m_pos.y - kPlatformHeight / 2,
		m_pos.x + kPlatformWidth / 2,
		m_pos.y + kPlatformHeight + 6,
		GetColor(100,100,100),
		true
	);
}

bool FallPlatTrap::IsActive() const
{
	return m_isActive;
}

Rect FallPlatTrap::GetRect() const
{
	return m_colRect;
}