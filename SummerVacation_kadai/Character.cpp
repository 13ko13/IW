#include "Character.h"
#include "Vec2.h"
#include "Player.h"
#include "DxLib.h"
#include "Bg.h"

namespace
{
	constexpr float kCharaSize = 32.0f;	//�L�����N�^�[�T�C�Y
	constexpr float kGravity = 0.7f;	//�d��
	constexpr float kGround = 144.0f;	//�n�ʈʒu
}

Character::Character() :
	m_state(PlayerState::Idle),
	m_handle(-1),
	m_handleIdle(-1),
	m_handleWalk(-1),
	m_handleShot(-1),
	m_handleJump(-1),
	m_handleDJump(-1),
	m_isTurn(true),
	m_isGround(true),
	m_pBg(nullptr)
{
}

Character::~Character()
{
	DeleteGraph(m_handle);
}

void Character::Init()
{

}

void Character::Update()
{
	m_isGround = false;

	Gravity();

	Rect chipRect;	//���������}�b�v�`�b�v�̋�`
	CheckHitMap(chipRect);

	if (m_isGround)
	{
		m_move.y = 0.0f;
	}
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

void Character::CheckHitMap(Rect& chipRect)
{
	//�����瓖���������`�F�b�N����
	m_pos.x += m_move.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize - 1, kCharaSize - 1);

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.GetLeft() - kCharaSize * 0.5f;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.GetRight() + kCharaSize * 0.5f;
		}
		m_move.x = 0.0f;
	}

	//�c���瓖���������`�F�b�N����
	m_pos.y += m_move.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize - 1, kCharaSize - 1);

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kCharaSize * 0.5f;
			m_move.y = 0.0f;
			m_isGround = true;
		}
		else if (m_move.y < 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kCharaSize * 0.5f;
			m_move.y *= -0.1f;
		}
	}

#ifdef _DEBUG
	//�����蔻��X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize, kCharaSize);
#endif
}