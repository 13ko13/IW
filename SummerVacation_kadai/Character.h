#pragma once
#include "Rect.h"
#include "Vec2.h"

class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//プレイヤーの現在の行動
	enum class PlayerState
	{
		Idle,
		Walk,
		Shot
	};

	PlayerState m_state;

protected:	
	void Gravity();

protected:
	int m_handle;
	//プレイヤーの入力待機中のグラフィックハンドル
	int m_handleIdle;
	//プレイヤーの歩き入力中のグラフィックハンドル
	int m_handleWalk;
	//プレイヤーの弾撃ち入力中のグラフィックハンドル
	int m_handleShot;

	//左右反転するか
	bool m_isTurn;
	//地面に着地しているか
	bool m_isGround;

	Vec2 m_pos;		//座標
	Vec2 m_move;	//移動
	Rect m_colRect;	//当たり判定用の矩形
};