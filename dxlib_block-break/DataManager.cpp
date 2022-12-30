#include "DataManager.h"
#include<fstream>
#include<Windows.h>
using namespace std;

ResultData DataManager::s_resultData = ResultData();

SaveData DataManager::LoadSaveData()
{
    //ファイルを開く
    std::ifstream fin("assets/data/savedData.txt");
    //ファイルが開けたか確認
    if (!fin) {
        MessageBox(nullptr, "セーブデータファイルを開けませんでした。", "ERROR", MB_OK);
    }

    std::string str;

    SaveData data;

    //ファイルから全文字列データを読み込み

    //ユーザー名データ取り出し
    getline(fin, str);
    data.name = str;

    //ハイスコアデータ取り出し
    getline(fin, str);
    data.highScore = stoi(str);


    //ファイルを閉じる
    fin.close();

    return data;
}

void DataManager::SaveSaveData(SaveData data)
{
    //ファイルを開く
    std::ofstream fout("assets/data/savedData.txt");
    //ファイルが開けたか確認
    if (!fout) {
        MessageBox(nullptr, "セーブデータファイルを開けませんでした。", "ERROR", MB_OK);
    }

    //ファイルにデータを書き込み    
    fout << data.name << "\n" << data.highScore << "\n";

    //ファイルを閉じる
    fout.close();
}
