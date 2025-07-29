#include "DxLib.h"
#include "Game.h"
#include "SceneMain.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight,0);

	SetWindowSizeChangeEnableFlag(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);
	SceneMain mainScene;
	mainScene.Init();

	while (ProcessMessage() == 0)
	{
		//画面をクリア
		ClearDrawScreen();

		//ESCキーが押されたらウィンドウを閉じる
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//ここにゲームの処理などを書く
		mainScene.Update();
		
		//描画
		mainScene.Draw();

		//裏画面の内容を表画面に反映
		ScreenFlip();

	}
	//メモリ上のグラフィックを開放
	mainScene.End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}