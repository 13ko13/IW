#include "Player.h"
#include "DxLib.h"

//定数定義
namespace
{
	//プレイヤーの開始位置
	constexpr int kPlayerStartX = 256;
	constexpr int kPlayerStartY = 128;

	//グラフィックのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 38;

	//アニメーション情報
	constexpr int kIdleAnimNum = 6;
	constexpr int kAnimWaitFrame = 5; //アニメ1コマ当たりのフレーム数

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
	if ((pad & PAD_INPUT_UP) != 0)	//&演算:ビット単位の演算
	{
		m_pos.y -= kSpeed;
	}
	if ((pad & PAD_INPUT_DOWN) != 0)	//&演算:ビット単位の演算
	{
		m_pos.y += kSpeed;
	}
	if ((pad & PAD_INPUT_RIGHT) != 0)	//&演算:ビット単位の演算
	{
		m_pos.x += kSpeed;
		m_isTurn = false;
	}
	if ((pad & PAD_INPUT_LEFT) != 0)	//&演算:ビット単位の演算
	{
		m_pos.x -= kSpeed;
		m_isTurn = true;
	}
}

void Player::Draw()
{
	//アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNo = m_animFrame / kAnimWaitFrame;

	//アニメーションの進行に合わせてグラフィックの切り取り位置を変更する
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	DrawRectGraph(static_cast<int>(m_pos.x) - kGraphWidth / 2,
		static_cast<int>(m_pos.y) - kGraphHeight / 2,
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		m_handle, true, m_isTurn
	);
}

