#include "DxLib.h"
#include "Game.h"

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
		

		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();

	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}