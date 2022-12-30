#include "Audio.h"
#include "DxLib.h"

Audio::Audio(const char* path)
{
	m_soundHandle = LoadSoundMem(path);
	if (m_soundHandle == -1) {
		MessageBox(nullptr, "音声ファイルの読み込みに失敗しました。", "ERROR", MB_OK);
	}
}

Audio::~Audio()
{
	DeleteSoundMem(m_soundHandle);
}

void Audio::Play()
{
	int vol = (int)(volume * 255.0f);
	ChangeVolumeSoundMem(vol, m_soundHandle);

	if (isLooping)
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_LOOP);
	else
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
}

void Audio::Pause()
{
	StopSoundMem(m_soundHandle);
}

bool Audio::IsPlaying() {
	if (CheckSoundMem(m_soundHandle) == 1) return true;
	return false;
}
