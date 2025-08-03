#include "Character.h"
#include "Vec2.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	constexpr float kCharaSize = 32.0f;	//キャラクターサイズ
	constexpr float kGravity = 0.1f;	//重力
	constexpr float kGround = 144.0f;	//地面位置
}

Character::Character() :
	m_state(PlayerState::Idle),
	m_handle(-1),
	m_handleIdle(-1),
	m_handleWalk(-1),
	m_isTurn(true),
	m_isGround(true)
{
}

Character::~Character()
{
}

void Character::Init()
{

}

void Character::Update()
{
	Gravity();

	//着地処理
	if (m_pos.y >= kGround)
	{
		m_pos.y = kGround;
		m_move.y = 0.0f;
		m_isGround = true;
	}

#ifdef _DEBUG
	//当たり判定更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize, kCharaSize);
#endif
}

void Character::Draw()
{
	float drawX = m_pos.x - kCharaSize * 0.5f;
	float drawY = m_pos.y - kCharaSize * 0.5f;

	
}

void Character::Gravity()
{
	m_move.y += kGravity;
}
