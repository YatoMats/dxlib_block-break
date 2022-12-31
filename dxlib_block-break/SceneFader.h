#pragma once
#include <string>

class Image;

class SceneFader {
protected:
	//フェード用パネル画像
	Image* m_panel;
	//パネル透明度
	float m_alpha;

	//フェード完了までの最低待ち時間
	float m_waitTime = 0.1f;//0.25f;
	//待ち時間計測用
	float m_timer = 0.0f;

public:
	SceneFader();
	virtual ~SceneFader();

	virtual void Update(){}
	virtual void Render();
};

//次のシーンへ遷移する際のフェードアウト処理
class SceneFadeOuter :public SceneFader 
{
	//次に読み込むシーン名
	std::string m_nextSceneName;

	//非同期で読み込むかどうか
	bool m_useAsync = true;

	bool m_isTriggered = false;
public:
	SceneFadeOuter();

	void Update()override;

	//読み込み開始のフラグを立てる
	void SetTrigger(const std::string& nextSceneName) { 
		m_isTriggered = true; m_nextSceneName = nextSceneName; 
	}
};

//シーン開始時のフェードイン処理
class SceneFadeInner : public SceneFader 
{
	//シーンフェード完了時フラグ
	bool m_isDone = false;
public:
	SceneFadeInner();

	void Update()override;
	void Render()override;
};