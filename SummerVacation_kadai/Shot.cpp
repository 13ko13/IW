#include "DxLib.h"
#include "Shot.h"

namespace
{
	constexpr float kSpeed = 10.0f;	//’e‚ÌˆÚ“®‘¬“x
}

Shot::Shot() : 
	m_pos({0,0}),
	m_handle(-1),
	m_move({ kSpeed,0 })
{
	m_handle = LoadGraph("data/Shot.gif");
}

Shot::~Shot()
{
	DeleteGraph(m_handle);
}

void Shot::Init()
{
}

void Shot::Update()
{
	m_pos += m_move;
}

void Shot::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_handle, true);
}

void Shot::SetInfo(const Vec2& pos, bool isTurn)
{
	m_pos = pos;

	if (!isTurn)
	{
		m_move.x = kSpeed;
	}
	else
	{
		m_move.x = -kSpeed;
	}
}