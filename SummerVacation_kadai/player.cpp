#include "Player.h"
#include "DxLib.h"
#include "Character.h"

//�萔��`
namespace
{
	//�v���C���[�̊J�n�ʒu
	constexpr int kPlayerStartX = 70;
	constexpr int kPlayerStartY = 123;

	//�O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 38;

	//�A�j���[�V�������
	constexpr int kIdleAnimNum = 6;
	constexpr int kAnimWaitFrame = 17; //�A�j��1�R�}������̃t���[����

	constexpr int kSpeed = 2;
}

Player::Player() :
	m_handle(-1),
	m_handleIdle(-1),
	m_handleWalk(-1),
	m_isTurn(false),
	m_isInput(false),
	m_animFrame(0),
	m_state(PlayerState::Idle)
{
}

Player::~Player()
{
}

void Player::Init(int handle,int handleIdle, int handleWalk)
{
	m_handle = handle;
	m_handleIdle = handleIdle;
	m_handleWalk = handleWalk;
	m_pos.x = kPlayerStartX;
	m_pos.y = kPlayerStartY;
	m_isTurn = false;
	m_isInput = false;
	m_animFrame = 0;
}

void Player::End()
{

}

void Player::Update()
{
	Character::Update();

	Move();

	Character::m_pos += m_move;

	if (m_isInput == false)
	{
		m_state = PlayerState::Idle;
	}
	//�A�j���X�V
	m_animFrame++;

	int animMax = 0;
	switch (m_state)
	{
	case PlayerState::Idle:
		m_handle = m_handleIdle;
		animMax = 11;
		break;
	case PlayerState::Walk:
		m_handle = m_handleWalk;
		animMax = 6;
		break;
	}

	if (m_animFrame >= kIdleAnimNum * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}

	m_isInput = false;
}

void Player::Move()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((pad & PAD_INPUT_RIGHT) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_move.x = kSpeed;
		m_isInput = true;
		m_state = PlayerState::Walk;
		m_pos.x += kSpeed;
		m_isTurn = false;
	}
	else if ((pad & PAD_INPUT_LEFT) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_move.x = -kSpeed;
		m_isInput = true;
		m_state = PlayerState::Walk;
		m_pos.x -= kSpeed;
		m_isTurn = true;
	}
	else
	{
		m_move.x = 0.0f;
	}
}

void Player::Draw()
{
	Character::Draw();

#ifdef _DEBUG
	//�����蔻���\��
	m_colRect.Draw(0x0000ff, false);
#endif

	//�A�j���[�V�����̃t���[��������\���������R�}�ԍ����v�Z�ŋ��߂�
	int animNo = m_animFrame / kAnimWaitFrame;

	//�A�j���[�V�����̐i�s�ɍ��킹�ăO���t�B�b�N�̐؂���ʒu��ύX����
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	DrawRectGraph(static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y) ,
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		m_handle, true, m_isTurn
	);
}

