#include "Character.h"
#include "Vec2.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	constexpr float kCharaSize = 50.0f;	//キャラクターサイズ
}

Character::Character()
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
#ifdef _DEBUG
	//当たり判定更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize, kCharaSize);
#endif
}

void Character::Draw()
{

}