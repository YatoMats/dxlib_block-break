#include "SoundEffectCommand.h"
#include "Audio.h"

void SoundEffectCommand::Execute() {
	//�Đ�����������A�R�}���h�I��
	if (!m_aud->IsPlaying()) 
		isDone = true;
}