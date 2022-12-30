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
	//シーン間でのゲームのリザルトデータのバッファ用
	static ResultData s_resultData;

public:
	//セーブデータ読み込み
	static SaveData LoadSaveData();
	//ファイルにセーブデータを書き込み
	static void SaveSaveData(SaveData data);

	static ResultData GetResultData() { return s_resultData; }
	static void SetResultData(ResultData data) { s_resultData = data; }
};