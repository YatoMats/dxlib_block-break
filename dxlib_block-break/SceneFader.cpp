#include "SceneFader.h"
#include "App.h"
#include "Image.h"
#include "SceneManager.h"

SceneFader::SceneFader()
	:m_panel(new Image("")), m_alpha(0.0f)
{
	//フェード用のパネル色
	m_panel->SetColor(0.5f, 0.5f, 0.5f);
}

SceneFader::~SceneFader()
{
	delete m_panel;
	m_panel = nullptr;
}

void SceneFader::Render()
{
	//ウィンドウ解像度
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();
	
	//シーンフェード用パネル描画
	m_panel->Render(0, 0, scrw, scrh);
}


SceneFadeOuter::SceneFadeOuter()
{
	//最初は透明に
	m_panel->alpha = 0.0f;
}

void SceneFadeOuter::Update()
{
	if (!m_isTriggered) return;

	//時間計測
	m_timer += 1.0f / App::GetFrameRate();
	if (m_timer > m_waitTime) {
		m_timer = 0.0f;

		//時間になったら、次のシーン読み込み
		if (m_useAsync)
			SceneManager::LoadSceneAsync(m_nextSceneName);
		else 
			SceneManager::LoadScene(m_nextSceneName);
	}
	//徐々にパネルを不透明に
	m_panel->alpha += m_timer / m_waitTime;
}


SceneFadeInner::SceneFadeInner()
{
	//最初は不透明に
	m_panel->alpha = 1.0f;
}

void SceneFadeInner::Update()
{
	//時間計測
	m_timer += 1.0f / App::GetFrameRate();
	if (m_timer > m_waitTime) {
		m_timer = 0.0f;

		//時間になったら、完了フラグを立てる
		m_isDone = true;
	}
	//徐々にパネルのを透明に
	m_panel->alpha -= m_timer / m_waitTime;
}

void SceneFadeInner::Render()
{
	if (m_isDone) return;

	//ウィンドウ解像度
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//シーンフェード用パネル描画
	m_panel->Render(0, 0, scrw, scrh);
}
