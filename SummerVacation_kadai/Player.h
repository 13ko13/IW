#pragma once
#include "Vec2.h"

class player
{
public:
	player();
	~player();

	void Init(int handle);
	void End();
	void Update();
	void Draw();

private:
	int m_handle;	//�v���C���[�̃O���t�B�b�N�n���h��

	Vec2 m_pos;
};

