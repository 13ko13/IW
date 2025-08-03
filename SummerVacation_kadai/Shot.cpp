#include "DxLib.h"
#include "Shot.h"

Shot::Shot() : 
	m_pos({0,0}),
	m_handle(-1)
{
}

Shot::~Shot()
{
	
}

void Shot::Init(int handle)
{
	m_handle = handle;
}

void Shot::Update()
{

}

void Shot::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_handle, true);
}