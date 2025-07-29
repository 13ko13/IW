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
	int m_tileGraphHandle;	//マップチップのグラフィック
	int m_bgGraphHandle;	//背景のグラフィック

	//背景
	Bg m_bg;
};

