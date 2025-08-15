#pragma once

#include "Rect.h"
#include "Vec2.h"

class Trap
{
public:
	Trap();
	~Trap();

	void Init(const Vec2& RtrapPos, const Vec2& UtrapPos, const Vec2& velocity, int RgraphHandle, int UgraphHnadle);
	void End();
	void Update();
	void Draw();

	bool IsActive() const;
	Rect GetRect() const;

private:
	//ハンドル関係
	int m_Rhandle;    // トラップの右向きグラフィックハンドル
	int m_Uhandle;    // トラップの上向きグラフィックハンドル

	//フラグ関係
	bool m_isActive;  // トラップがアクティブかどうか

	Vec2 m_RtrapPos;        // 右向きトラップの位置
	Vec2 m_UtrapPos;        // 上向きトラップの位置
	Vec2 m_velocity;  // トラップの移動速度

	Rect m_RtrapColRect;  // 右向きトラップ当たり判定用の矩形
	Rect m_UtrapColRect;  // 上向きトラップ当たり判定用の矩形
};

