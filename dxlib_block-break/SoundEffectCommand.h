#pragma once
#include "Command.h"

class Audio;

//�G�t�F�N�g�Đ������܂ő҂�
class SoundEffectCommand : public Command {
	Audio* m_aud;
public:
	SoundEffectCommand(Audio* aud) :m_aud(aud) { }
	void Execute()override;
};
