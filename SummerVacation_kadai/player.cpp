#include "Player.h"
#include "DxLib.h"
#include "Character.h"

//定数定義
namespace
{
	//プレイヤーの開始位置
	constexpr int kPlayerStartX = 70;
	constexpr int kPlayerStartY = 123;

	//グラフィックのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 38;

	//アニメーション情報
	constexpr int kIdleAnimNum = 6;
	constexpr int kAnimWaitFrame = 17; //アニメ1コマ当たりのフレーム数

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
	//アニメ更新
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
	if ((pad & PAD_INPUT_RIGHT) != 0)	//&演算:ビット単位の演算
	{
		m_move.x = kSpeed;
		m_isInput = true;
		m_state = PlayerState::Walk;
		m_pos.x += kSpeed;
		m_isTurn = false;
	}
	else if ((pad & PAD_INPUT_LEFT) != 0)	//&演算:ビット単位の演算
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
	//当たり判定を表示
	m_colRect.Draw(0x0000ff, false);
#endif

	//アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNo = m_animFrame / kAnimWaitFrame;

	//アニメーションの進行に合わせてグラフィックの切り取り位置を変更する
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	DrawRectGraph(static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y) ,
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		m_handle, true, m_isTurn
	);
}

