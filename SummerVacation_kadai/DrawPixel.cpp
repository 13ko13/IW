#include "DxLib.h"
#include "Game.h"
#include "SceneMain.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight,0);

	SetWindowSizeChangeEnableFlag(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	SceneMain mainScene;
	mainScene.Init();

	while (ProcessMessage() == 0)
	{
		//��ʂ��N���A
		ClearDrawScreen();

		//ESC�L�[�������ꂽ��E�B���h�E�����
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//�����ɃQ�[���̏����Ȃǂ�����
		mainScene.Update();
		
		//�`��
		mainScene.Draw();

		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();

	}
	//��������̃O���t�B�b�N���J��
	mainScene.End();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}