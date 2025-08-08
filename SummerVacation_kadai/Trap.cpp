#include "Trap.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kTrapSize = 16.0f; // �g���b�v�̃T�C�Y
	constexpr float kScale = 2.0f; // �g���b�v�̊g�嗦
	constexpr int kRightSpikeIndex = 1; // �E�����g���b�v�̃C���f�b�N�X
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
	//�O���t�B�b�N�폜��TrapManager�ōs��
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
	if (!m_isActive) return;	//�g���b�v���A�N�e�B�u�łȂ��ꍇ�͍X�V���Ȃ�

	m_pos += m_velocity;

	//��ʊO�ɏo�����A�N�e�B�u�ɂ���
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
	if (!m_isActive) return; //�g���b�v���A�N�e�B�u�łȂ��ꍇ�͕`�悵�Ȃ�

	int srcX = kTrapSize * kRightSpikeIndex; // �E�����g���b�v�̐؂���ʒu
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