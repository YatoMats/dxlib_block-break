#include "DataManager.h"
#include<fstream>
#include<Windows.h>
using namespace std;

ResultData DataManager::s_resultData = ResultData();

SaveData DataManager::LoadSaveData()
{
    //�t�@�C�����J��
    std::ifstream fin("assets/data/savedData.txt");
    //�t�@�C�����J�������m�F
    if (!fin) {
        MessageBox(nullptr, "�Z�[�u�f�[�^�t�@�C�����J���܂���ł����B", "ERROR", MB_OK);
    }

    std::string str;

    SaveData data;

    //�t�@�C������S������f�[�^��ǂݍ���

    //���[�U�[���f�[�^���o��
    getline(fin, str);
    data.name = str;

    //�n�C�X�R�A�f�[�^���o��
    getline(fin, str);
    data.highScore = stoi(str);


    //�t�@�C�������
    fin.close();

    return data;
}

void DataManager::SaveSaveData(SaveData data)
{
    //�t�@�C�����J��
    std::ofstream fout("assets/data/savedData.txt");
    //�t�@�C�����J�������m�F
    if (!fout) {
        MessageBox(nullptr, "�Z�[�u�f�[�^�t�@�C�����J���܂���ł����B", "ERROR", MB_OK);
    }

    //�t�@�C���Ƀf�[�^����������    
    fout << data.name << "\n" << data.highScore << "\n";

    //�t�@�C�������
    fout.close();
}
