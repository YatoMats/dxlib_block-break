#include "SoundEffectCommand.h"
#include "Audio.h"

void SoundEffectCommand::Execute() {
	//再生完了したら、コマンド終了
	if (!m_aud->IsPlaying()) 
		isDone = true;
}