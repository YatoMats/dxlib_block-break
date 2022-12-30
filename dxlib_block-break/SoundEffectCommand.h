#pragma once
#include "Command.h"

class Audio;

//エフェクト再生完了まで待つ
class SoundEffectCommand : public Command {
	Audio* m_aud;
public:
	SoundEffectCommand(Audio* aud) :m_aud(aud) { }
	void Execute()override;
};
