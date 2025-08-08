#pragma once
#include "Bg.h"
#include "Player.h"
#include "Shot.h"
#include "TrapManager.h"

class Player;
class Shot;
class Bg;

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
	void UpdateShot(); //�e�X�V
	void DeleteShot(int index); //�e�폜

private:
	//�g�p����O���t�B�b�N
	int m_playerIdleGraphHandle;	//�v���C���[�̃A�C�h���O���t�B�b�N
	int m_playerWalkGraphHandle;	//�v���C���[�̕����O���t�B�b�N
	int m_playerShotGraphHnadle;	//�v���C���[�̒e�����O���t�B�b�N
	int m_playerJumpGraphHandle;	//�v���C���[�̃W�����v�O���t�B�b�N
	int m_playerDJumpGraphHandle;	//�v���C���[�̓�i�W�����v�O���t�B�b�N
	int m_tileGraphHandle;			//�}�b�v�`�b�v�̃O���t�B�b�N
	int m_bgGraphHandle;			//�w�i�̃O���t�B�b�N
	int m_bulletGraphHandle;			//�e�̃O���t�B�b�N
	int m_trapGraphHandle;			//�g���b�v�̃O���t�B�b�N

	//�g�Q���ˍς݃t���O
	bool m_isTrapFired = false;

	//�v���C���[
	Player* m_pPlayer;
	//�w�i
	Bg* m_pBg;
	//�e
	Shot* m_pShot[5];
	//�g���b�v�}�l�[�W���[
	TrapManager m_trapManager;
};

