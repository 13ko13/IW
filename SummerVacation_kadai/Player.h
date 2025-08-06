#pragma once
#include "Vec2.h"
#include "Character.h"
#include "Shot.h"

class Shot;

class Player : public Character
{
public:
	Player();
	virtual ~Player();

	virtual void Init(int handle,int handleRun, int handleWalk,int handleShot) ;
	void End();
	virtual void Update() override;
	virtual void Draw()override;
	Shot* CreateShot();

private:
	//移動
	void Move();
	//ジャンプ
	void Jump();
	//弾のクールタイム
	void ShotCT(); 

private:
	//押された瞬間だけをとるための前回の入力状態
	int prevInput = 0;

	//プレイヤーが入力状態かどうかのフラグ
	bool m_isInput;
	//プレイヤーが弾を発射している状態かどうかのフラグ
	bool m_isShotInput;

	//アニメーション関連
	int m_animFrame;	//アニメーションのフレーム数
	int m_shotAnimTime; //Shot状態を維持するための時間カウント

	//時間関連
	int m_time;	//時間を計測
};