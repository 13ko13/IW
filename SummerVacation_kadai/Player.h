#pragma once
#include "Vec2.h"
#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	void Init(int handle,int handleRun, int handleWalk);
	void End();
	void Update();
	void Draw();

private:
	//プレイヤーの現在の行動
	enum class PlayerState
	{
		Idle,
		Walk
	};

private:
	//移動
	void Move();

	//プレイヤーの基盤グラフィックハンドル
	int m_handle;
	//プレイヤーの入力待機中のグラフィックハンドル
	int m_handleIdle;	
	//プレイヤーの歩き入力中のグラフィックハンドル
	int m_handleWalk;

	Vec2 m_pos;

	//左右反転するか
	bool m_isTurn;
	//プレイヤーが入力状態かどうかのフラグ
	bool m_isInput;

	//アニメーション関連
	int m_animFrame;	//アニメーションのフレーム数

	PlayerState m_state;
};

