#pragma once
#include "Vec2.h"

class Shot
{
public:
	Shot();
	~Shot();

	void Init(int handle);
	void Update();
	void Draw();

private:
	Vec2 m_pos;		//�e�̈ʒu
	int m_handle;	//�O���t�B�b�N�n���h��
};

