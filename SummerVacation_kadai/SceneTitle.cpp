#include "SceneTitle.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_titleGraphHandle(-1),
	m_pressGraphHandle(-1),
	m_currentSeq(Seq::SeqFadeIn),
	m_fadeAlpha(0),
	m_isFadeIn(false),
	m_isFadeOut(false),
	m_pressFrame(0)
{

}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_titleGraphHandle = LoadGraph("data/Title.png");
}
