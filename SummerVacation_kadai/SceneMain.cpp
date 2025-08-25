#include "SceneMain.h"
#include "DxLib.h"
#include "Bg.h"
#include "player.h"
#include "Trap.h"
#include "Shot.h"
#include "Game.h"
#include "TrapManager.h"
#include "Shuriken.h"

namespace
{
	constexpr int kShotMax = 5;	//1度に撃てる最大弾数
	constexpr int kFadeFrame = 30; //フェードにかかるフレーム数
}

SceneMain::SceneMain() :
	m_playerIdleGraphHandle(-1),
	m_playerWalkGraphHandle(-1),
	m_playerShotGraphHnadle(-1),
	m_playerJumpGraphHandle(-1),
	m_playerDJumpGraphHandle(-1),
	m_tileGraphHandle(-1),
	m_bgGraphHandle(-1),
	m_bulletGraphHandle(-1),
	m_RtrapGraphHandle(-1),
	m_UtrapGraphHandle(-1),
	m_LtrapGraphHandle(-1),
	m_BtrapGraphHandle(-1),
	m_platformGraphHandle(-1),
	m_moveSpikeGraphHandle(-1),
	m_shurikenGraphHandle(-1),
	m_goalGraphHandle(-1),
	m_clearFontHandle(-1),
	m_isRtrapFired(false),
	m_isPlatformSpawned(false),
	m_isUtrapSpawned(false),
	m_isLtrapSpawned(false),
	m_isBtrapSpawned(false),
	m_isMoveSpikeSpawned(false),
	m_gameSeq(SeqFadeIn),
	m_frameCount(0),
	m_fadeFrame(0)
{
	m_pPlayer = new Player;
	for (int i = 0; i < kShotMax; i++)
	{
		m_pShot[i] = nullptr;
	}

	m_pShuriken = new Shuriken;

	m_pBg = new Bg;
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{

	m_frameCount = 0;

	//フェード状態の初期化
	m_fadeFrame = 0;

	//グラフィックをロードする
	m_playerIdleGraphHandle = LoadGraph("data/idle.png");
	m_playerWalkGraphHandle = LoadGraph("data/Run.png");
	m_playerShotGraphHnadle = LoadGraph("data/Shoot.png");
	m_playerJumpGraphHandle = LoadGraph("data/Jump.png");
	m_playerDJumpGraphHandle = LoadGraph("data/Jump.png");
	m_tileGraphHandle = LoadGraph("data/tileset.png");
	m_bgGraphHandle = LoadGraph("data/3-bg-full.png");
	m_RtrapGraphHandle = LoadGraph("data/SpikeTrap.png");
	m_UtrapGraphHandle = LoadGraph("data/SpikeTrap.png");
	m_LtrapGraphHandle = LoadGraph("data/SpikeTrap.png");
	m_BtrapGraphHandle = LoadGraph("data/SpikeTrap.png");
	m_platformGraphHandle = LoadGraph("data/fakeTileset.png");
	m_moveSpikeGraphHandle = LoadGraph("data/MoveSpike.png");
	m_shurikenGraphHandle = LoadGraph("data/Shuriken.png");
	m_goalGraphHandle = LoadGraph("data/Goal.png");

	//フォントのロード
	m_clearFontHandle = CreateFontToHandle("HGP創英角ﾎﾟｯﾌﾟ体", 120, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//プレイヤーの初期化
	m_pPlayer->Init(
		m_playerIdleGraphHandle, m_playerIdleGraphHandle,
		m_playerWalkGraphHandle, m_playerShotGraphHnadle,
		m_playerJumpGraphHandle, m_playerDJumpGraphHandle);

	//背景の初期化
	m_pBg->Init();

	//トラップの初期化
	m_trapManager.Init(
		m_RtrapGraphHandle, m_UtrapGraphHandle,
		m_LtrapGraphHandle, m_BtrapGraphHandle);

	//消える地面の初期化
	m_platformManager.Init(m_platformGraphHandle);

	//プレイヤーにプラットフォームマネージャーをセット
	m_pPlayer->SetPlatformManager(&m_platformManager);

	//プレイヤーのポインタを取得
	m_goal.SetPlayer(m_pPlayer);

	//移動トゲの初期化
	m_moveSpikeMgr.Init(m_moveSpikeGraphHandle);

	//手裏剣の初期化
	m_pShuriken->Init(m_shurikenGraphHandle);

	//ゴールの初期化
	m_goal.Init(m_goalGraphHandle);

	//手裏剣のポインタをプレイヤーにセット
	m_pShuriken->SetPlayer(m_pPlayer);

	//トゲ発射イベント(X:1000,Y:300を越えたら)
	if (m_pPlayer->GetPos().x > 1100.0f &&
		m_pPlayer->GetPos().y > 200.0f &&
		m_pPlayer->GetPos().y <= 300.0f &&
		!m_isRtrapFired)
	{
		m_trapManager.SpawnTrap(
			{ 0.0f, 300.0f }, { -15.0f,-15.0f },
			{ -15.0f, -15.0f }, { -15.0f,-15.0f },
			{ 40.0f,   0.0f }); //右に飛ぶトゲ

		m_trapManager.SpawnTrap(
			{ 0.0f, 280.0f }, { -15.0f,-15.0f },
			{ -15.0f, -15.0f }, { -15.0f,-15.0f },
			{ 40.0f,   0.0f }); //右に飛ぶトゲ

		m_isRtrapFired = true; // トゲを発射済みフラグを立てる
	}

	//上向きトゲを設置
	if (!m_isUtrapSpawned)
	{
		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { 848.0f, 304.0f },
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 上向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { 176.0f, 624.0f },
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 上向きトゲ

		m_isUtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//左向きトゲを設置
	if (!m_isLtrapSpawned)
	{
		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 368.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 400.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 432.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 464.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 492.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_isLtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//下向きトゲを設置
	if (!m_isBtrapSpawned)
	{
		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ -15.0f,  632.0f }, { 240.0f,  528.0f },
			{ 0.0f,   0.0f }); // 下向きトゲ

		m_isBtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//プレイヤーとの当たり判定
	if (m_trapManager.CheckCollision(m_pPlayer->GetColRect()) ||
		m_moveSpikeMgr.CheckCollision(m_pPlayer->GetColRect()) ||
		m_pShuriken->CheckCollision(m_pPlayer->GetColRect()))
	{
		//プレイヤーがトゲに当たった場合の処理
		printfDx("トゲに当たった！\n");
	}

	//プラットフォーム生成
	if (!m_isPlatformSpawned)
	{
		//プラットフォームを生成
		m_platformManager.SpawnPlatform({ 736.0f, 168.0f }, 10.0f); // 60フレーム後に落下開始
		m_isPlatformSpawned = true; // プラットフォームを生成済みフラグを立てる
	}

	//移動トゲ生成
	if (!m_isMoveSpikeSpawned)
	{
		//移動トゲを生成
		m_moveSpikeMgr.SpawnSpike({ 400.0f, 363.0f }, { 0.0f, 0.0f }); // 初期位置と速度

		m_moveSpikeMgr.SpawnSpike({ 630.0f, 518.0f }, { 0.0f, 1.0f }); // 初期位置と速度

		m_moveSpikeMgr.SpawnSpike({ 700.0f, 630.0f }, { 0.0f, 1.0f }); // 初期位置と速度

		m_isMoveSpikeSpawned = true; // 移動トゲを生成済みフラグを立てる
	}

	//初期シーケンスの決定
	m_gameSeq = SeqFadeIn;

}

void SceneMain::End()
{
	m_pPlayer->End();
	m_pBg->End();
	//グラフィックを開放
	DeleteGraph(m_playerIdleGraphHandle);
	DeleteGraph(m_playerWalkGraphHandle);
	DeleteGraph(m_playerShotGraphHnadle);
	DeleteGraph(m_playerJumpGraphHandle);
	DeleteGraph(m_playerDJumpGraphHandle);
	DeleteGraph(m_tileGraphHandle);
	DeleteGraph(m_bgGraphHandle);
	DeleteGraph(m_bulletGraphHandle);
	DeleteGraph(m_RtrapGraphHandle);
	DeleteGraph(m_UtrapGraphHandle);
	DeleteGraph(m_LtrapGraphHandle);
	DeleteGraph(m_BtrapGraphHandle);
	DeleteGraph(m_platformGraphHandle);
	DeleteGraph(m_moveSpikeGraphHandle);
	DeleteGraph(m_shurikenGraphHandle);
	DeleteGraph(m_goalGraphHandle);

	//フォントの削除
	DeleteFontToHandle(m_clearFontHandle);
}

void SceneMain::Update()
{
	//現在のシーケンスの経過フレーム数をカウント
	m_frameCount++;
	switch (m_gameSeq)
	{
	case SeqFadeIn:
		UpdateFadeIn();
		break;
	case SeqGame:
		UpdateGame();
		break;
	case SeqClear:
		UpdateClear();
		break;
	case SeqGameOver:
		UpdateGameOver();
		break;
	}
}

void SceneMain::Draw()
{
	// 背景の描画
	m_pBg->Draw();

	// ゴールの描画
	m_goal.Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

	//手裏剣の描画
	m_pShuriken->Draw();

	// 弾の描画
	if (!m_pShot) return;
	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i]) continue;
		m_pShot[i]->Draw();
	}

	// トラップの描画
	m_trapManager.Draw();
	m_platformManager.Draw();
	m_moveSpikeMgr.Draw();

	// フェードの描画
	int fadeAlpha = 0;

	//フレームカウントをフェードの進行度（割合)に変換
	float fadeProgress = static_cast<float>(m_fadeFrame) / kFadeFrame;
	//255 -> 0 に変化させたいので割合を逆転させる
	fadeProgress = 1.0f - fadeProgress;
	//割合をかけることで現在のフェード値を決定する
	fadeAlpha = 255 * fadeProgress;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す

	//文字を中央に表示する
	int strWidth = GetDrawFormatStringWidthToHandle(
					m_clearFontHandle,
					"CLEAR!");

	//クリア表示
	if (m_goal.IsClear())
	{
		int x = (Game::kScreenWidth / 2 - strWidth / 2);
		int y = (Game::kScreenHeight / 2 - 60);
		DrawStringToHandle(
			x, y, "CLEAR!",
			GetColor(255, 1, 1),
			m_clearFontHandle);
	}
}

void SceneMain::UpdateShot()
{
	Shot* newShot = nullptr;
	if (m_pPlayer)
	{
		newShot = m_pPlayer->CreateShot();
	}
	if (newShot != nullptr)
	{
		for (int i = 0; i < kShotMax; i++)
		{
			if (m_pShot[i] == nullptr)
			{
				m_pShot[i] = newShot;
				break;
			}
		}
	}

	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		// 画面外に出た場合
		bool isOffScreen = m_pShot[i]->GetPos().x < 0 || m_pShot[i]->GetPos().x > Game::kScreenWidth;
		if (isOffScreen) DeleteShot(i);
	}
}

void SceneMain::DeleteShot(int index)
{
	if (!m_pShot[index]) return;

	delete m_pShot[index];
	m_pShot[index] = nullptr;
}

void SceneMain::UpdateFadeIn()
{
	//フェードインの進行
	m_fadeFrame++;
	if (m_fadeFrame > kFadeFrame)
	{
		//フェードイン完了
		m_fadeFrame = kFadeFrame;
		m_gameSeq = SeqGame; //シーケンスをゲームプレイに変更
		m_frameCount = 0; //フレームカウントをリセット
	}
}

void SceneMain::UpdateGame()
{
#ifdef _DEBUG
	//ボタン一発でクリアできるデバッグ機能

	//Xボタンを押したらクリアする
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//padのXボタンもしくはキーボードのCを押したとき
	if ((pad & PAD_INPUT_3) != 0)
	{
		//勝利条件を満たすような処理を書く
		m_goal.m_isClear = true;
		m_gameSeq = SeqClear; //シーケンスをクリアに変更
	}
#endif // _DEBUG

	m_pPlayer->Update();
	m_trapManager.Update();
	m_platformManager.Update(m_pPlayer->GetColRect());
	m_moveSpikeMgr.Update();
	m_pShuriken->Update();
	m_goal.Update();

	//トゲ発射イベント(X:1000,Y:300を越えたら)
	if (m_pPlayer->GetPos().x > 1100.0f &&
		m_pPlayer->GetPos().y > 200.0f &&
		m_pPlayer->GetPos().y <= 300.0f &&
		!m_isRtrapFired)
	{
		m_trapManager.SpawnTrap(
			{ 0.0f, 300.0f }, { -15.0f,-15.0f },
			{ -15.0f, -15.0f }, { -15.0f,-15.0f },
			{ 40.0f,   0.0f }); //右に飛ぶトゲ

		m_trapManager.SpawnTrap(
			{ 0.0f, 280.0f }, { -15.0f,-15.0f },
			{ -15.0f, -15.0f }, { -15.0f,-15.0f },
			{ 40.0f,   0.0f }); //右に飛ぶトゲ

		m_isRtrapFired = true; // トゲを発射済みフラグを立てる
	}

	//上向きトゲを設置
	if (!m_isUtrapSpawned)
	{
		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { 848.0f, 304.0f },
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 上向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { 176.0f, 624.0f },
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 上向きトゲ

		m_isUtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//左向きトゲを設置
	if (!m_isLtrapSpawned)
	{
		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 368.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 400.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 432.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 464.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ 1233.0f, 492.0f }, { -15.0f, -15.0f },
			{ 0.0f,   0.0f }); // 左向きトゲ

		m_isLtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//下向きトゲを設置
	if (!m_isBtrapSpawned)
	{
		m_trapManager.SpawnTrap(
			{ -15.0f, -15.0f }, { -15.0f, -15.0f },
			{ -15.0f,  632.0f }, { 240.0f,  528.0f },
			{ 0.0f,   0.0f }); // 下向きトゲ

		m_isBtrapSpawned = true; // トゲを設置済みフラグを立てる
	}

	//プレイヤーとの当たり判定
	if (m_trapManager.CheckCollision(m_pPlayer->GetColRect()) ||
		m_moveSpikeMgr.CheckCollision(m_pPlayer->GetColRect()) ||
		m_pShuriken->CheckCollision(m_pPlayer->GetColRect()))
	{
		//プレイヤーがトゲに当たった場合の処理
		printfDx("トゲに当たった！\n");
	}

	//プラットフォーム生成
	if (!m_isPlatformSpawned)
	{
		//プラットフォームを生成
		m_platformManager.SpawnPlatform({ 736.0f, 168.0f }, 10.0f); // 60フレーム後に落下開始
		m_isPlatformSpawned = true; // プラットフォームを生成済みフラグを立てる
	}

	//移動トゲ生成
	if (!m_isMoveSpikeSpawned)
	{
		//移動トゲを生成
		m_moveSpikeMgr.SpawnSpike({ 400.0f, 363.0f }, { 0.0f, 0.0f }); // 初期位置と速度

		m_moveSpikeMgr.SpawnSpike({ 630.0f, 518.0f }, { 0.0f, 1.0f }); // 初期位置と速度

		m_moveSpikeMgr.SpawnSpike({ 700.0f, 630.0f }, { 0.0f, 1.0f }); // 初期位置と速度

		m_isMoveSpikeSpawned = true; // 移動トゲを生成済みフラグを立てる
	}

	//クリアしたかどうか
	if (m_goal.IsClear())
	{
		m_gameSeq = SeqClear; //シーケンスをクリアに変更
		m_frameCount = 0; //フレームカウントをリセット
	}

	if (!m_pShot) return;

	UpdateShot();
}

void SceneMain::UpdateClear()
{
	//クリアしたときの処理
	//クリア表示
	m_pPlayer->Update();
}

void SceneMain::UpdateGameOver()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((pad & PAD_INPUT_1) != 0)
	{
		m_pPlayer->Init(
			m_playerIdleGraphHandle, m_playerIdleGraphHandle,
			m_playerWalkGraphHandle, m_playerShotGraphHnadle,
			m_playerJumpGraphHandle, m_playerDJumpGraphHandle);

		m_pBg->Init();

		m_goal.Init(m_goalGraphHandle);

		m_gameSeq = SeqGame;
		m_frameCount = 0;
	}
}
