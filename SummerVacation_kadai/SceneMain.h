#pragma once
#include "Bg.h"
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	int m_tileGraphHandle;	//�}�b�v�`�b�v�̃O���t�B�b�N
	int m_bgGraphHandle;	//�w�i�̃O���t�B�b�N

	//�w�i
	Bg m_bg;
};

