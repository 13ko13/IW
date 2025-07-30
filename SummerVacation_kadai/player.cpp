#include "Player.h"
#include "DxLib.h"

//�萔��`
namespace
{
	//�v���C���[�̊J�n�ʒu
	constexpr int kPlayerStartX = 256;
	constexpr int kPlayerStartY = 128;

	constexpr int kSpeed = 4;
}

player::player() :
	m_handle(-1)
{
}

player::~player()
{
}

void player::Init(int handle)
{
	m_handle = handle;
	m_pos.x = kPlayerStartX;
	m_pos.y = kPlayerStartY;
}

void player::End()
{

}

void player::Update()
{
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
	}
	if ((pad & PAD_INPUT_LEFT) != 0)	//&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_pos.x -= kSpeed;
	}
}

void player::Draw()
{

}

