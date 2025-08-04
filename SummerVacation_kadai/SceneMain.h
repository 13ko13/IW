#pragma once
#include "Bg.h"
#include "Player.h"
#include "Shot.h"

class Player;
class Shot;

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
	void UpdateShot();

private:
	//�g�p����O���t�B�b�N
	int m_playerIdleGraphHandle;	//�v���C���[�̃A�C�h���O���t�B�b�N
	int m_playerWalkGraphHandle;	//�v���C���[�̕����O���t�B�b�N
	int m_tileGraphHandle;	//�}�b�v�`�b�v�̃O���t�B�b�N
	int m_bgGraphHandle;	//�w�i�̃O���t�B�b�N
	int m_shotGraphHandle;	//�e�̃O���t�B�b�N

	//�v���C���[
	Player* m_pPlayer;
	//�w�i
	Bg m_bg;
	//�e
	Shot* m_pShot;
};

