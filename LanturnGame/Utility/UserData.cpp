#include "UserData.h"
#include "DxLib.h"
//#include <iostream>
#include <sstream>
//#include <vector>
#include <string.h>
char UserData::buf[1024];
char UserData::c;


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
	case 2:
		strcpy_s(name, "Resources/sounds.csv");
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
	case 2:
		strcpy_s(name, "Resources/sounds.csv");
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
	return 0;
}

float UserData::Test(int filenum, int num)
{
	float temp = 0;
	FILE* fp = nullptr;
	char name[64] = { "\0" };
	switch (filenum) {
	case 0:
		strcpy_s(name, "Resources/setting.csv");
		strcat_s(name, "\0");
		break;
	case 1:
		strcpy_s(name, "Resources/hiscore.csv");
		strcat_s(name, "\0");
		break;
	case 2:
		strcpy_s(name, "Resources/sounds.csv");
		strcat_s(name, "\0");
		break;
	}

	// �t�@�C���I�[�v��
	int result = fopen_s(&fp, name, "r");

	if (fp == NULL)
	{
		return -1;
	}

	// �����̓ǂ񂾉�
	int cnt = 0;

	// ,���΂�����
	int col = 0;

	// �w�肵����܂ŃX�L�b�v����
	while (1)
	{
		// �w�肵����Ȃ烋�[�v�𔲂���
		if (col == num) {
			break;
		}
		// �w�肵���񂶂�Ȃ��Ȃ�col++����
		if (fgetc(fp) == ',' || fgetc(fp) == EOF)
		{
			col++;
		}

	}

	while (1)
	{
		while (1)
		{
			// �������擾
			c = fgetc(fp);
			buf[cnt] = c;

			// �w�肵�������Ȃ烋�[�v�𔲂���
			if (c == ',' || c == '\n' || c == EOF)
			{
				buf[cnt] = '\0';
				break;
			}
			cnt++;
		}

		// �w�肵�������Ȃ烋�[�v�𔲂���
		if (c == '\n' || c == EOF)
		{
			break;
		}

		// �ǂݍ��񂾕�����𐔒l�ɂ���
		temp = atof(buf);
		cnt = 0;
		memset(buf, 0, sizeof(buf));
		break;
	}
	fclose(fp);
	memset(buf, 0, sizeof(buf));
	// �ǂݍ��񂾐��l��Ԃ�
	return temp;
}

float UserData::Test2(int filenum, int num, float data)
{
	// �t�@�C���ǂݍ���
	FILE* fp = nullptr;
	fopen_s(&fp, "Resources/sounds.csv", "r");
	if (fp == NULL)
	{
		return -1;
	}

	// �����̓ǂ񂾉�
	int cnt = 0;

	// ,��ʂ�����
	int textnum = 0;
	char charbuf[2][128] = { "\0" };
	while (1)
	{
		while (1)
		{
			// �������擾
			c = fgetc(fp);
			buf[cnt] = c;
			cnt++;
			// �w�肵�������Ȃ烋�[�v�𔲂���
			if (c == ',' || c == '\n' || c == EOF)
			{
				break;
			}
		}

		// �w�肵������X�L�b�v����
		// �w�肵������O�Ȃ當����0�ɕۑ�
		if (textnum < num)
		{
			strcat_s(charbuf[0], 128, buf);
		}

		// �w�肵�������Ȃ當����1�ɕۑ�
		if (textnum > num)
		{
			strcat_s(charbuf[1], 128, buf);
		}

		// buf�ɔz�u����ʒu��������
		cnt = 0;
		memset(buf, 0, sizeof(buf));

		// ,��ʂ�����++
		textnum++;

		// �w�肵�������Ȃ烋�[�v�𔲂���
		if (c == '\n' || c == EOF)
		{
			break;
		}
	}

	// �t�@�C�������
	fclose(fp);
	memset(buf, 0, sizeof(buf));

	// char�z��쐬
	char databuf[16] = "\0";

	// char�z��Ɉ����̐��l������
	sprintf_s(databuf, "%f,", data);

	// ������0��char�z���A��
	strcat_s(charbuf[0], 128, databuf);

	// ������0�ƕ�����1��A��
	strcat_s(charbuf[0], 128, charbuf[1]);

	// �t�@�C�����J��
	fopen_s(&fp, "Resources/sounds.csv", "w");

	if (fp == NULL)
	{
		return -1;
	}

	// �t�@�C���ɐ��l�̏�������
	fprintf(fp, "%s\n", charbuf[0]);

	// �t�@�C�������
	fclose(fp);
	return 0;
}
