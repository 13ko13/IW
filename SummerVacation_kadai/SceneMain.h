#pragma once
#include "Bg.h"
#include "Player.h"

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
	//�g�p����O���t�B�b�N
	int m_playerIdleGraphHandle;	//�v���C���[�̃A�C�h���O���t�B�b�N
	int m_playerWalkGraphHandle;	//�v���C���[�̕����O���t�B�b�N
	int m_tileGraphHandle;	//�}�b�v�`�b�v�̃O���t�B�b�N
	int m_bgGraphHandle;	//�w�i�̃O���t�B�b�N

	//�v���C���[
	Player m_player;
	//�w�i
	Bg m_bg;
};

