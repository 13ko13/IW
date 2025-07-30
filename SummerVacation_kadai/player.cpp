#include "Player.h"
#include "DxLib.h"

//�萔��`
namespace
{
	//�v���C���[�̊J�n�ʒu
	constexpr int kPlayerStartX = 256;
	constexpr int kPlayerStartY = 128;

	//�O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 38;

	//�A�j���[�V�������
	constexpr int kIdleAnimNum = 6;
	constexpr int kAnimWaitFrame = 5; //�A�j��1�R�}������̃t���[����

	constexpr int kSpeed = 4;
}

Player::Player() :
	m_handle(-1),
	m_isTurn(false),
	m_animFrame(0)
{
}

Player::~Player()
{
}

void Player::Init(int handle)
{
	m_handle = handle;
	m_pos.x = kPlayerStartX;
	m_pos.y = kPlayerStartY;
	m_isTurn = false;
	m_animFrame = 0;
}

void Player::End()
{

}

void Player::Update()
{
	m_animFrame++;
	if (m_animFrame >= kIdleAnimNum * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((pad & PAD_INPUT_UP) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_pos.y -= kSpeed;
	}
	if ((pad & PAD_INPUT_DOWN) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_pos.y += kSpeed;
	}
	if ((pad & PAD_INPUT_RIGHT) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_pos.x += kSpeed;
		m_isTurn = false;
	}
	if ((pad & PAD_INPUT_LEFT) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_pos.x -= kSpeed;
		m_isTurn = true;
	}
}

void Player::Draw()
{
	//�A�j���[�V�����̃t���[��������\���������R�}�ԍ����v�Z�ŋ��߂�
	int animNo = m_animFrame / kAnimWaitFrame;

	//�A�j���[�V�����̐i�s�ɍ��킹�ăO���t�B�b�N�̐؂���ʒu��ύX����
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	DrawRectGraph(static_cast<int>(m_pos.x) - kGraphWidth / 2,
		static_cast<int>(m_pos.y) - kGraphHeight / 2,
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		m_handle, true, m_isTurn
	);
}

