#pragma once
#include "Scene.h"
#include "Vec2.h"
#include <vector>
#include "DataManager.h"

class Actor;
class Command;
class Button;
class SceneFadeOuter;
class SceneFadeInner;

class MainScene : public Scene 
{
	//�S�A�N�^�[�̔z��
	std::vector<Actor*> m_actors;

	//�R�}���h���X�g
	std::vector<Command*> m_cmds;

	//�v���C���[�p�h��
	Actor* m_paddle;
	//�{�[��
	Actor* m_ball;

	//SE
	Audio* m_paddleSE;
	Audio* m_blockSE;
	Audio* m_fallSE;

	//BGM
	Audio* m_bgm;
	//�w�i�摜
	Image* m_bgImg;

	//���ԕ\���p�e�L�X�g
	Text* m_timeText;
	//HP�\���p�e�L�X�g
	Text* m_hpText;

	//HP�\���p�n�[�g�摜
	std::vector<Image*> m_heartImgs;

	//�{�[������
	const Vec2 m_ballStartVeloc = Vec2(300, -300);
	//�{�[�����x
	Vec2 m_ballVeloc = m_ballStartVeloc;

	//�O�t���[���ł̃}�E�X�ʒu
	Vec2 m_preMousePos;

	//�v���C���[HP
	int m_hp = 3;
	//�Q�[�����̌o�ߎ���
	float m_time = 0;

	//�Q�[����̑��u���b�N��
	int m_blockCounts = 0;

	//�Q�[�����s�t���O
	bool m_isGameOver = false;
	//�Q�[�������t���O
	bool m_isGameClear = false;

	//�{�[�������㎞����
	bool m_isBallFallen = false;

	//�Q�[���|�[�Y���t���O
	bool m_isPaused = false;
	
	//�|�[�Y���Ȃǂł̕\���p�p�l��
	Image* m_panelImg;
	//�p�l����̃^�C�g���e�L�X�g
	Text* m_panelTitle;
	//�p�l����̑���������̃e�L�X�g
	Text* m_panelDesc;
	//�p�l����̃{�^��
	Button* m_pnlBtnTitle;
	Button* m_pnlBtnRe;
	Button* m_pnlBtnGame;

	//�|�[�Y�p�l��������SE
	Audio* m_pnlPopSE;
	//�|�[�Y�p�l���j����SE
	Audio* m_pnlDeSE;

	//���U���g�V�[���֓n���A�Q�[���̌��ʏ��
	ResultData m_resultData;

	//�V�[���t�F�[�h�p
	SceneFadeInner* m_fadeInner;
	SceneFadeOuter* m_fadeOuter;

	//�V�[���t�F�[�h�A�E�g��SE
	Audio* m_faderSE;

public:
	//�u���b�N�����Q�[���I������
	~MainScene();
	//�u���b�N�����Q�[���J�n����
	void Start()override;
	//�u���b�N�����Q�[���X�V����
	void Update()override;
	//�u���b�N�����Q�[���`�揈��
	void Render()override;

	//�{�[�����������u�Ԃ̏���
	void OnBallFallEnter();
	//�{�[���������Ԏ�����
	void OnBallFall();

	//�Q�[���|�[�Y������
	void OnGamePause();

	//�Q�[���I��������
	void OnGameEnds();
};