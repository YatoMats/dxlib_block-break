#pragma once

class Audio {
	int m_soundHandle;
public:
	bool isLooping = false;
	float volume = 1.0f;
public:
	Audio(const char* path);
	~Audio();

	void Play();
	void Pause();

	bool IsPlaying();
};