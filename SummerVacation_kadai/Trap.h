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
	Vec2 m_pos;        // �g���b�v�̈ʒu
	Vec2 m_velocity;  // �g���b�v�̈ړ����x
	int m_handle;    // �g���b�v�̃O���t�B�b�N�n���h��
	bool m_isActive;  // �g���b�v���A�N�e�B�u���ǂ���
	Rect m_colRect;  // �����蔻��p�̋�`
};

