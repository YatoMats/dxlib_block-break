#include "MainScene.h"
#include <windows.h>
#include "Actor.h"
#include "Command.h"
#include "Collision.h"
#include "SoundEffectCommand.h"
#include "Button.h"
#include "SceneFader.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

//TODO:�p�h�����~�`�ɁB�Փˌ�A�{�[���̉����o��������
// 
//TODO: ���Ԍo�߂Ń{�[�����x�A�b�v
//TODO:�E�B���h�E�T�C�Y�ɉ����āA�u���b�N�������Ȃǂ�ς���

//TODO:�|�[�Y�p�l���N���X
//TODO:HPUI�N���X
//TODO:TimerUI�N���X

//TODO:UI Slider
//TODO:UI InputField
//TODO:Config 

void MainScene::Start()
{
	//�����V�[�h�l�ݒ�
	srand((unsigned int)time(NULL));

	//�W���̃t�H���g�T�C�Y��ݒ�
	Text::SetDefaultFontSize(33);

	//�X�N���[��������
	float scrw = (float)App::GetResolutionWidth();
	float scrh = (float)App::GetResolutionHeight();


	//BGM
	m_bgm = new Audio("assets/aud/bgm/newworld.mp3");
	m_bgm->isLooping = true;
	m_bgm->volume = 0.33f;
	m_bgm->Play();

	//�w�i�摜
	m_bgImg = new Image("assets/img/cosmos.png");


	//�t�F�[�h�p�I�u�W�F�N�g�쐬
	m_fadeOuter = new SceneFadeOuter();
	m_fadeInner = new SceneFadeInner();

	//�V�[���t�F�[�h�A�E�g��SE
	m_faderSE = new Audio("assets/aud/se/decision3.mp3");
	m_faderSE->volume = 1.0f;


	//HP�\���p�e�L�X�g�����ݒ�
	m_hpText = new Text("HP:");// +std::to_string(m_hp));
	m_hpText->SetColor(0, 0.8f, 0);

	//HP�\���p�n�[�gUI�摜�ǂݍ���
	for (int i = 0; i < m_hp; i++) {
		Image* h = new Image("assets/img/heart.png");
		m_heartImgs.push_back(h);
	}


	//���ԕ\���p�e�L�X�g
	m_timeText = new Text("TIME 00:00");
	m_timeText->SetColor(0, 0.8f, 0);


	//�p�l���ݒ�
	m_panelImg = new Image("");
	m_panelImg->alpha = 0.93f;
	m_panelImg->SetColor(0.8f, 0.8f, 0.8f);

	//�p�l���^�C�g���e�L�X�g
	m_panelTitle = new Text("PAUSE");
	m_panelTitle->SetColor(1.0f, 0.0f, 1.0f);
	m_panelTitle->ChangeFontSize(44);

	//�p�l����������e�L�X�g
	m_panelDesc = new Text(
		"Press any Key to Back to the Game..."
	);
	m_panelDesc->SetColor(0.2f, 0.2f, 0.2f);


	//�p�l���{�^���T�C�Y
	int btnw = 200;
	int btnh = 50;

	//�^�C�g���ցA�p�l���{�^���ݒ�
	Text* toTitleTxt = new Text("�^�C�g����");
	toTitleTxt->ChangeFontSize(24);
	toTitleTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_pnlBtnTitle = new Button(new Image(""), toTitleTxt ,
		25, (int)scrh - btnh - 100,
		btnw, btnh);
	//�{�^���N���b�N���A
	m_pnlBtnTitle->SetOnClick([=]() {
		//�V�[���t�F�[�h�A�E�g��SE�Đ�
		m_faderSE->Play();
		//�^�C�g���V�[���֑J��
		m_fadeOuter->SetTrigger("TitleScene");
		//SceneManager::LoadScene("TitleScene");
		});

	//�Q�[���֖߂�A�p�l���{�^���ݒ�
	Text* toGameTxt = new Text("�Q�[���֖߂�");
	toGameTxt->ChangeFontSize(24);
	toGameTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_pnlBtnGame = new Button(new Image(""), toGameTxt,
		(int)scrw / 2 - btnw / 2, (int)scrh - btnh - 100,
		btnw, btnh);
	m_pnlBtnGame->SetOnClick([=]() {
		m_isPaused = !m_isPaused;
		});

	//���߂���A�p�l���{�^���ݒ�
	Text* reTxt = new Text("���߂���");
	reTxt->ChangeFontSize(24);
	reTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_pnlBtnRe = new Button(new Image(""), reTxt,
		(int)scrw - btnw - 25, (int)scrh - btnh - 100,
		btnw, btnh);
	m_pnlBtnRe->SetOnClick([=]() {
		//�V�[���t�F�[�h�A�E�g��SE�Đ�
		m_faderSE->Play();
		//���C���V�[���֑J��
		m_fadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadScene("MainScene");
		});

	//�p�l��������SE
	m_pnlPopSE = new Audio("assets/aud/se/decision2.mp3");
	m_pnlPopSE->volume = 0.8f;
	//�p�l��������SE
	m_pnlDeSE = new Audio("assets/aud/se/cancel2.mp3");
	m_pnlDeSE->volume = 1.0f;


	//�v���C���[�p�h���쐬�A�ݒ�
	Image* pdlImg = new Image("");
	pdlImg->shape = Shape::Circle;
	m_paddle = new Actor(
		pdlImg,				//�摜���
		scrw / 2, scrh - 50,	//�ʒu
		80, 80					//�T�C�Y
	);
	//�A�N�^�[���X�g�ɒǉ�
	m_actors.push_back(m_paddle);


	//�{�[���摜�ݒ�
	Image* ballImg = new Image("");
	ballImg->shape = Shape::Circle;
	//�{�[�����a
	float br = 38;
	//�{�[�������ʒux���W�������_����
	float bx = (float)Math::RandRange((int)br, (int)(scrw - br));
	//�{�[���A�N�^�[
	m_ball = new Actor(
		ballImg,
		bx, m_paddle->pos.y - 75,	//�ʒu
		br, br						//�T�C�Y
	);
	m_actors.push_back(m_ball);


	//�u���b�N�s��̍���ʒu
	float ox = 120;
	float oy = 120;
	//�u���b�N�Ԃ̃X�y�[�X
	float sx = 10;
	float sy = 10;
	//�u���b�N������
	float w = 60;
	float h = 60;
	//�u���b�N�s����쐬
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 8; x++) {
			//�u���b�N�摜
			Image* blockImg = new Image("");
			blockImg->shape = Shape::Circle;
			//�u���b�N�A�N�^�[�ݒ�
			Actor* block = new Actor(
				blockImg,
				ox + x * (w + sx), oy + y * (h + sy),	//�ʒu
				w, h									//�T�C�Y
			);
			//�A�N�^�[���X�g�ɒǉ�
			m_actors.push_back(block);

			//�u���b�N���f�[�^�����Z
			m_blockCounts++;
		}
	}

	//�p�h���ւ̏Փˎ�SE
	m_paddleSE = new Audio("assets/aud/se/decision.mp3");
	m_paddleSE->volume = 1.0f;
	//�{�[��������SE
	m_fallSE = new Audio("assets/aud/se/bomb.mp3");
	m_fallSE->volume = 1.0f;
	//�u���b�N�Ƃ̏Փˎ�SE
	m_blockSE = new Audio("assets/aud/se/cancel.mp3");
	m_blockSE->volume = 1.0f;

	//�}�E�X�J�[�\���ʒu�擾
	m_preMousePos = InputManager::GetMousePos();
}

MainScene::~MainScene()
{
	//�������������
	Release(m_bgm);
	Release(m_bgImg);

	Release(m_hpText);
	Release(m_timeText);

	Release(m_paddleSE);
	Release(m_fallSE);
	Release(m_blockSE);

	Release(m_panelImg);
	Release(m_panelTitle);
	Release(m_panelDesc);
	
	Release(m_pnlBtnTitle);
	Release(m_pnlBtnGame);
	Release(m_pnlBtnRe);

	Release(m_pnlPopSE);
	Release(m_pnlDeSE);

	Release(m_fadeInner);
	Release(m_fadeOuter);
	Release(m_faderSE);

	for (Image* h : m_heartImgs) {
		delete h;
	}

	//�S�A�N�^�[�̏I������
	for (Actor* a : m_actors) {
		delete a;
	}
	//�c���Ă���R�}���h�̏I������
	for (Command* c : m_cmds) {
		delete c;
	}
}

void MainScene::Update()
{
	//�V�[���t�F�[�h�X�V����
	m_fadeInner->Update();
	m_fadeOuter->Update();

	//�Q�[���I�����莞�A
	if (m_isGameOver || m_isGameClear)
	{
		//�Q�[���I��������
		OnGameEnds();
		return;
	}

	//�Q�[�����Ȃ�A
	if(!m_isPaused)
	{
		if (InputManager::GetKeyEnter(KEY_ID::ESC) ||
			InputManager::GetKeyEnter(KEY_ID::MOUSE_LEFT) ||
			InputManager::GetKeyEnter(KEY_ID::MOUSE_MIDDLE) ||
			InputManager::GetKeyEnter(KEY_ID::MOUSE_RIGHT))
		{
		}
		//�Q�[�����ɁA��L�ȊO�̂����ꂩ�̃L�[�������ꂽ��A
		else if (InputManager::GetAnyKeyEnter())
		{
			//�p�l��������SE�Đ�
			m_pnlPopSE->Play();
			//�|�[�Y���t���O�؂�ւ�
			m_isPaused = !m_isPaused;
		}
	}
	//�|�[�Y���Ȃ�A
	else 
	{
		//�|�[�Y������
		OnGamePause();
		//�A�N�^�[�X�V���̏������΂�
		return;
	}

	//�{�[��������ԂȂ�A
	if (m_isBallFallen) 
	{
		//�{�[���������̏���
		OnBallFall();
		//�A�N�^�[�X�V���̏������΂�
		return;
	}

	//�R�}���h���X�g����
	/*for (int i = (int)m_cmds.size() - 1; i >= 0; i--) {
		Command* c = m_cmds[i];
		//�R�}���h�X�V����
		c->Execute();
		//�R�}���h�I���Ȃ�A�R�}���h���X�g���珜��
		if (c->isDone) {
			delete c;
			m_cmds.erase(m_cmds.begin() + i);
		}
	}
	//�R�}���h���s���Ȃ�A�Q�[�����ꎞ��~
	if (m_cmds.size() != 0) return;*/


	//�X�N���[��������
	float scrw = (float)App::GetResolutionWidth();
	float scrh = (float)App::GetResolutionHeight();

	//�}�E�X�J�[�\���ʒu
	Vec2 mp = InputManager::GetMousePos();

	//�v���C���[�p�h���ʒu
	Vec2 p = m_paddle->pos;
	//�v���C���[�p�h���T�C�Y
	float pw = m_paddle->size.x;
	float ph = m_paddle->size.y;

	//�{�[�����x
	Vec2 bv = m_ballVeloc;
	//�{�[���ʒu
	Vec2 b = m_ball->pos;
	//�{�[���T�C�Y
	float br = m_ball->size.x / 2;


	//�}�E�X�ړ��ʂɉ����āA�v���C���[�ʒu��ύX
	p.x = mp.x;
	//p.y = mp.y;
	//�v���C���[�ʒu���A�͈͓��։����߂�
	if (p.x - pw / 2 < 0) p.x = pw / 2;
	else if (scrw < p.x + pw / 2) p.x = scrw - pw / 2;


	//�{�[�����x�x�N�g���������ɋ߂��Ȃ�A�O���������Ȃ���

	//�{�[���O���������ɋ߂��A
	if (Math::Abs(bv.y) < 0.03f) {
		//�E����
		if (0 < bv.x) {
			//�������Ȃ�A���v���ɉ�]
			if (0 < bv.y) bv.Rotate(3);
			//������Ȃ�A�����v���ɉ�]
			else bv.Rotate(-3);
		}
		//������
		else {
			//�������Ȃ�A�����v���ɉ�]
			if (0 < bv.y) bv.Rotate(-3);
			//������Ȃ�A���v���ɉ�]
			else bv.Rotate(3);
		}
	}
	//�{�[���O���������ɋ߂��A
	/*else if (Math::Abs(bv.x) < 0.03f) {
		//������
		if (0 < bv.y) {
			//�E�����Ȃ�A���v���ɉ�]
			if (0 < bv.x) bv.Rotate(3);
			//�������Ȃ�A�����v���ɉ�]
			else bv.Rotate(-3);
		}
		//�����
		else {
			//�E�����Ȃ�A���v���ɉ�]
			if (0 < bv.x) bv.Rotate(3);
			//�������Ȃ�A�����v���ɉ�]
			else bv.Rotate(-3);
		}
	}*/


	//���x(pix/s)�ɉ����āA�{�[���ړ�
	b += bv * 1.0f / (float)App::GetFrameRate();

	//�{�[�����X�e�[�W�[�ɓ��B������A���˕Ԃ�
	//�X�e�[�W�E�[�Փˎ��A
	if (b.x - br < 0) {
		b.x = br;
		bv.x *= -1.0f;
	}
	//���[
	else if (scrw < b.x + br) {
		b.x = scrw - br;
		bv.x *= -1.0f;
	}
	//��[
	if (b.y - br < 0) {
		b.y = br;
		bv.y *= -1.0f;
	}
	//�{�[�����X�e�[�W��ɗ�������A
	else if (scrh < b.y - br)
	{
		//�{�[���ʒu��߂�
		//�{�[�������ʒux���W�������_����
		b.x = (float)Math::RandRange((int)br, (int)(scrw - br));
		b.y = p.y - 100;
		//�{�[�����x�������l��
		bv = m_ballStartVeloc;

		//�{�[�������������u�Ԃ̏���
		OnBallFallEnter();
	}


	//�{�[���ƃu���b�N�Ƃ̋�����2����v�Z
	float dpow = b.DistancePow(p);
	float pr = pw / 2;
	//�{�[���ƃu���b�N���������Ă�����A
	if (dpow < Math::Pow2(br + pr))
	{
		//�{�[�����x�x�N�g���𔽎�
		bv.Reflect(p.DirectionTo(b));

		//SE�Đ�
		m_paddleSE->Play();
	}
	//�{�[�����p�h���ɓ���������A
	//if (HitCheck::CircleToBox(b, br, p, pw, ph))
	/*if (HitCheck::CircleToCircle(b, br, p, pw))
	{						
		//�{�[�����x�x�N�g���𔽎�
		bv.Reflect(p.DirectionTo(b));

		//��`����
		/*Vec2 min = Vec2(p.x - pw / 2, p.y - ph / 2);
		//��`�E��
		Vec2 max = Vec2(p.x + pw / 2, p.y + ph / 2);

		//�p�ɓ��������ꍇ�̔��ˌv�Z
		//��`4���_�Ɖ~�Ƃ̓����蔻��
		if (b.DistancePow(min) < Math::Pow2(br)) {
			//�{�[�����p�h�����㒸�_��荶�㑤�Ȃ�A
			if ((b.x < min.x) && (b.y < min.y)) {
				//�����߂�����
				//�{�[���ʒu���p�h���̏��
				//b.y = p.y - ph / 2 - br;
				//���˃x�N�g���v�Z
				bv.Reflect(min.DirectionTo(b));
			}
		}
		else if (b.DistancePow(Vec2(max.x, min.y)) < Math::Pow2(br)) {
			//�{�[�����p�h���E�㒸�_���E�㑤�Ȃ�A
			if ((max.x < b.x) && (b.y < min.y)) {
				//���˃x�N�g���v�Z
				bv.Reflect(Vec2(max.x, min.y).DirectionTo(b));
			}
		}
		/*else if (b.DistancePow(Vec2(min.x, max.y)) < Math::Pow2(br)) {
			//���˃x�N�g���v�Z
			bv.Reflect(Vec2(min.x, max.y).DirectionTo(b));
		}
		else if (b.DistancePow(max) < Math::Pow2(br)) {
			//���˃x�N�g���v�Z
			bv.Reflect(max.DirectionTo(b));
		}*//*
		//�p�ȊO�̔��ˌv�Z
		else
		{
			//�{�[���ʒu���p�h���̏��
			b.y = p.y - ph / 2 - br;
			//�{�[�����x�x�N�g���𔽎�
			bv.y *= -1.0f;
		}
		//SE�Đ�
		m_paddleSE->Play();
	}*/

	//�{�[���ƃu���b�N�Ƃ̓����蔻��
	for (int i = (int)m_actors.size() - 1; i >= 2; i--) {
		Actor* a = m_actors[i];

		//�{�[�����a
		float r = m_ball->size.x / 2;
		//�u���b�N���a
		float r2 = a->size.x / 2;
		//�u���b�N�ʒu
		Vec2 ap = a->pos;

		//�{�[���ƃu���b�N�Ƃ̋�����2����v�Z
		float dpow = b.DistancePow(ap);

		//�{�[���ƃu���b�N���������Ă�����A
		if (dpow < Math::Pow(r + r2, 2.0f))
		{
			//�{�[�����x�x�N�g���𔽎�
			bv.Reflect(ap.DirectionTo(b));

			//�u���b�N��j��
			delete a;
			//���X�g����j��
			m_actors.erase(m_actors.begin() + i);
			//�u���b�N����0�ȉ��ɂȂ�����A�Q�[���N���A�����
			if (--m_blockCounts <= 0) m_isGameClear = true;

			//SE�Đ�
			m_blockSE->Play();
		}
	}

	//�p�h���̈ʒu�ψيm��
	m_paddle->pos = p;
	//�{�[���̈ʒu�A���x�ψيm��
	m_ball->pos = b;
	m_ballVeloc = bv;
	//�}�E�X�ʒu��ۑ�
	m_preMousePos = mp;


	//�o�ߎ��Ԍv�Z
	m_time += 1.0f / (float)App::GetFrameRate();
	//���b�ϊ�
	int sec = (int)m_time % 60;
	int min = (int)m_time / 60 % 60;
	//������ϊ�
	std::string minStr = std::to_string(min);
	std::string secStr = std::to_string(sec);
	//�[������
	if (sec < 10) secStr = "0" + secStr;
	if (min < 10) minStr = "0" + minStr;
	//���ԕ\���p�e�L�X�g�ɐݒ�
	m_timeText->SetText("TIME " + minStr + ":" + secStr);
}

void MainScene::Render()
{
	//�X�N���[��������
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//�w�i�摜�̕`��
	m_bgImg->Render(-1, -1, scrw + 1, scrh + 1);

	//�S�A�N�^�[�̕`��
	for (Actor* a : m_actors) {
		a->Render();
	}

	//UI�`��
	//HP�p�n�[�g�摜�`��
	for (int i = 0; i < m_heartImgs.size(); i++) {
		m_heartImgs[i]->Render(i * 50 + scrw / 2/*+300*/, 10, 50, 50);
	}
	//�v���C���[HP�e�L�X�g�`��
	m_hpText->Render(scrw / 2 - 50, 15);

	//���ԕ\���p�e�L�X�g�`��
	m_timeText->Render(50, 10);

	//�|�[�Y���̃p�l����`��
	if (m_isPaused) 
	{
		m_panelImg->Render(0, 0, scrw, scrh);

		int tw = m_panelTitle->GetStringWidth();
		m_panelTitle->Render(scrw / 2 - tw / 2, 100);

		int dw = m_panelDesc->GetStringWidth();
		m_panelDesc->Render(/*100*/scrw / 2 - dw / 2, 300);

		m_pnlBtnTitle->Render();
		m_pnlBtnGame->Render();
		m_pnlBtnRe->Render();
	}

	//�t�F�[�h�p�p�l���`��
	m_fadeInner->Render();
	m_fadeOuter->Render();
}

void MainScene::OnBallFallEnter()
{
	//�{�[��������Ԃ�
	//m_isBallFallen = true;

	//SE�Đ�
	m_fallSE->Play();
	
	//HP�����炷
	if (--m_hp <= 0) {
		//HP���O�ȉ��ɂȂ�����A
		//�Q�[���I���t���O�𗧂Ă�
		m_isGameOver = true;
	}
	//HP��1�ȉ��ɂȂ�����A�ԕ�����
	else if (m_hp <= 1) {
		m_hpText->SetColor(1.0f, 0, 0);
	}
	//HP��2�ȉ��ɂȂ�����A��������
	else if (m_hp <= 2) {
		m_hpText->SetColor(1.0f, 1.0f, 0);
	}

	//HP�\���X�V
	//m_hpText->SetText("HP:" + std::to_string(m_hp));

	//HP�\���p�n�[�g�摜�����炷
	if (m_hp >= 0)
	{
		Release(m_heartImgs[m_hp]);
		m_heartImgs.erase(m_heartImgs.begin() + m_hp);
	}
}

void MainScene::OnBallFall()
{
	//�����҂��Ă���A�ʒu�Ƒ��x��߂�������
	/*m_ballFallTimer += 1.0f / (float)App::fps;
	if (m_ballFallTimer > m_ballFallSpan)
	{
		m_ballFallTimer = 0.0f;

		m_ball->pos = Vec2(0, 0);
		m_ballVeloc = m_ballStartVeloc;

		m_isBallFall = false;
	}*/
}

void MainScene::OnGamePause()
{
	//�f�o�b�O�p����
	/*if (InputManager::GetKeyEnter(KEY_ID::R)) {
		//�Q�[���I�����p�����[�^�����ꎞ�ۑ�
		ResultData result;
		result.isSuccess = true;//m_isGameClear;
		result.hp = m_hp;
		result.time = (int)m_time;

		//�X�R�A�v�Z
		int hpPt = m_hp * m_hp * 100;
		int t = 1;
		//if (m_time > 0)
		t = (int)m_time;
		int timePt = 10000 - t * 50;
		if (timePt < 0) timePt = 1000;
		result.score = hpPt + timePt;

		DataManager::SetResultData(result);

		m_fadeOuter->SetTrigger("ResultScene");
	}

	else*/
	if (InputManager::GetKeyEnter(KEY_ID::ESC)||
		InputManager::GetKeyEnter(KEY_ID::MOUSE_LEFT)||
		InputManager::GetKeyEnter(KEY_ID::MOUSE_MIDDLE)||
		InputManager::GetKeyEnter(KEY_ID::MOUSE_RIGHT)
		)
	{
	}
	//�|�[�Y���ɁA��L�ȊO�̂����ꂩ�̃L�[�������ꂽ��A
	else if (InputManager::GetAnyKeyEnter())
	{
		//�p�l��������SE�Đ�
		m_pnlDeSE->Play();

		//�|�[�Y���t���O�؂�ւ�
		m_isPaused = !m_isPaused;
	}

	//�p�l���{�^���X�V����
	m_pnlBtnGame->Update();
	m_pnlBtnRe->Update();
	m_pnlBtnTitle->Update();
}

void MainScene::OnGameEnds()
{
	//�Q�[���I�����p�����[�^�����ꎞ�ۑ�
	ResultData result;
	result.isSuccess = m_isGameClear;
	result.hp = m_hp;
	result.time = (int)m_time;

	//�X�R�A�v�Z
	int hpPt = m_hp * m_hp * 100;
	int t = 1;
	//if (m_time > 0)
		t = (int)m_time;
	int timePt = 10000 - t * 50;
	if (timePt < 0) timePt = 1000;
	result.score = hpPt + timePt;

	DataManager::SetResultData(result);

	//���ʃV�[���ɑJ��
	m_fadeOuter->SetTrigger("ResultScene");
	//SceneManager::LoadScene("ResultScene");
}
