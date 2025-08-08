#pragma once

#include "Rect.h"
#include "Vec2.h"

class Trap
{
public:
	Trap();
	~Trap();

	void Init(const Vec2& pos, const Vec2& velocity, int graphHandle);
	void End();
	void Update();
	void Draw();

	bool IsActive() const;
	Rect GetRect() const;

private:
	Vec2 m_pos;        // トラップの位置
	Vec2 m_velocity;  // トラップの移動速度
	int m_handle;    // トラップのグラフィックハンドル
	bool m_isActive;  // トラップがアクティブかどうか
	Rect m_colRect;  // 当たり判定用の矩形
};

