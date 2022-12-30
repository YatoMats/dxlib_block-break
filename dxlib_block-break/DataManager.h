#pragma once
#include <string>

class ResultData {
public:
	int score = 0;
	int time = -1;
	int hp = -1;
	bool isSuccess = false;
};

class SaveData {
public:
	std::string name = "User Name";
	int highScore = 0;
};

class DataManager {
	//�V�[���Ԃł̃Q�[���̃��U���g�f�[�^�̃o�b�t�@�p
	static ResultData s_resultData;

public:
	//�Z�[�u�f�[�^�ǂݍ���
	static SaveData LoadSaveData();
	//�t�@�C���ɃZ�[�u�f�[�^����������
	static void SaveSaveData(SaveData data);

	static ResultData GetResultData() { return s_resultData; }
	static void SetResultData(ResultData data) { s_resultData = data; }
};