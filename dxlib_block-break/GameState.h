#pragma once

class GameState {

public:
	virtual void OnEnter() { }
	virtual GameState* Update() { return this; }
	//virtual void Render() { }
};

class MainState :public GameState {
public:
	void OnEnter()override{}
	GameState* Update()override { return this; }
};

class PauseState: public GameState {
public:
	void OnEnter()override{}
	GameState* Update()override { return this; }
};

class GameClearState : public GameState {
public:
	void OnEnter()override {}
	GameState* Update()override { return this; }
};

class GameOverState : public GameState {
public:
	void OnEnter()override {}
	GameState* Update()override { return this; }
};
