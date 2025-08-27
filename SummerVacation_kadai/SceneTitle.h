#pragma once

class SceneMain;

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void End();
	void Update();
	void Draw();

	void SetSceneMain(SceneMain* pSceneMain);

	void UpdateTitle();		//タイトル
	void UpdateFadeIn();	//フェードイン
	void UpdateFadeOut();	//フェードアウト

	//シーケンス
	enum Seq
	{
		SeqTitle,	//タイトル
		SeqFadeIn,	//フェードイン
		SeqFadeOut,	//フェードアウト

		SeqNum	//シーケンスの数
	};

private:

	//使用するグラフィック
	int m_titleGraphHandle; //タイトルのグラフィックハンドル
	int m_bgGraphHandle;    //背景のグラフィックハンドル
	
	//フォントハンドル
	int m_startFontHandle; //PressStartのグラフィックハンドル
	
	//シーケンス管理
	int m_currentSeq;	//現在のシーケンス

	//フェード関係
	int m_fadeAlpha;	//フェード用のアルファ値

	//フラグ関係
	bool m_isFadeIn;	//フェードイン中かどうかのフラグ
	bool m_isFadeOut;	//フェードアウト中かどうかのフラグ

	//アニメーション関係
	int m_pressFrame;   //PressStartの点滅用フレームカウント

	//シーンメイン
	SceneMain* m_pSceneMain;
};

