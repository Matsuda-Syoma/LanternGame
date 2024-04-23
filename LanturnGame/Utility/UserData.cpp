#include "UserData.h"
#include "DxLib.h"
#include <string.h>

float UserData::LoadData(int i)
{
	float temp = 0;
	FILE* fp = nullptr;
	char name[64] = { "\0" };
	switch (i) {
	case 0:
		strcpy_s(name, "Resources/setting.csv");
		strcat_s(name,"\0");
		break;
	case 1:
		strcpy_s(name, "Resources/hiscore.csv");
		strcat_s(name, "\0");
		break;
	}

	// �t�@�C���I�[�v��
	int result = fopen_s(&fp, name, "r");

	// �G���[�`�F�b�N
	if (result != 0) {
		printf("err : LoadData");
		return -1.f;
	}

	fscanf_s(fp, "%f,\n", &temp);

	//�t�@�C���N���[�Y
	fclose(fp);
	return temp;
}

int UserData::SaveData(int i, float data)
{
	FILE* fp = nullptr;
	char name[64] = { "\0" };
	switch (i) {
	case 0:
		strcpy_s(name, "Resources/setting.csv");
		strcat_s(name, "\0");
		break;
	case 1:
		strcpy_s(name, "Resources/hiscore.csv");
		strcat_s(name, "\0");
		break;
	}

	// �t�@�C���I�[�v��
	int result = fopen_s(&fp, name, "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		printf("err : SaveData");
		return -1;
	}
	fprintf(fp, "%f,\n", data);
	fclose(fp);
}
