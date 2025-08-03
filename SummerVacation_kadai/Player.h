#pragma once
#include "Vec2.h"
#include "Character.h"
#include "Shot.h"

class Player : public Character
{
public:
	Player();
	virtual ~Player();

	virtual void Init(int handle,int handleRun, int handleWalk);
	void End();
	virtual void Update() override;
	virtual void Draw()override;
	Shot* CreateShot();

private:
	//移動
	void Move();
	//ジャンプ
	void Jump();

	//Vec2 m_pos;
	
	//プレイヤーが入力状態かどうかのフラグ
	bool m_isInput;

	//アニメーション関連
	int m_animFrame;	//アニメーションのフレーム数


};

