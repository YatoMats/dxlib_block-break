#pragma once
#include <string>

#include "Image.h"
#include "Text.h"
#include "Audio.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "App.h"

class Scene {
private:
	std::string m_name;

public:
	virtual ~Scene() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}

	const std::string& GetName() { return m_name; }

private:
	void SetName(const std::string& name) { m_name = name; }

	friend class SceneManager;
};
