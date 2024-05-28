#include "UserData.h"
#include "DxLib.h"
//#include <iostream>
#include <sstream>
//#include <vector>
#include <string.h>
char UserData::buf[1024];
char UserData::c;

float UserData::LoadData(int filenum, int num)
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

	// ファイルオープン
	int result = fopen_s(&fp, name, "r");

	if (fp == NULL)
	{
		return -1;
	}

	// 文字の読んだ回数
	int cnt = 0;

	// ,を飛ばした回数
	int col = 0;

	// 指定した列までスキップする
	while (1)
	{
		// 指定した列ならループを抜ける
		if (col == num) {
			break;
		}
		// 指定した列じゃないならcol++する
		if (fgetc(fp) == ',' || fgetc(fp) == EOF)
		{
			col++;
		}

	}

	while (1)
	{
		while (1)
		{
			// 文字を取得
			c = fgetc(fp);
			buf[cnt] = c;

			// 指定した文字ならループを抜ける
			if (c == ',' || c == '\n' || c == EOF)
			{
				buf[cnt] = '\0';
				break;
			}
			cnt++;
		}

		// 指定した文字ならループを抜ける
		if (c == '\n' || c == EOF)
		{
			break;
		}

		// 読み込んだ文字列を数値にする
		temp = atof(buf);
		cnt = 0;
		memset(buf, 0, sizeof(buf));
		break;
	}
	fclose(fp);
	memset(buf, 0, sizeof(buf));
	// 読み込んだ数値を返す
	return temp;
}

float UserData::LoadData(int filenum)
{
	return LoadData(filenum, 0);
}

float UserData::SaveData(int filenum, int num, float data)
{
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

	// ファイルオープン
	int result = fopen_s(&fp, name, "w");

	//エラーチェック
	if (result != 0)
	{
		printf("err : SaveData");
		return -1;
	}

	// 文字の読んだ回数
	int cnt = 0;

	// ,を通った回数
	int textnum = 0;
	char charbuf[2][128] = { "\0" };
	while (1)
	{
		while (1)
		{
			// 文字を取得
			c = fgetc(fp);
			buf[cnt] = c;
			cnt++;
			// 指定した文字ならループを抜ける
			if (c == ',' || c == '\n' || c == EOF)
			{
				break;
			}
		}

		// 指定した列をスキップする
		// 指定した列より前なら文字列0に保存
		if (textnum < num)
		{
			strcat_s(charbuf[0], 128, buf);
		}

		// 指定した列より後なら文字列1に保存
		if (textnum > num)
		{
			strcat_s(charbuf[1], 128, buf);
		}

		// bufに配置する位置を初期化
		cnt = 0;
		memset(buf, 0, sizeof(buf));

		// ,を通った回数++
		textnum++;

		// 指定した文字ならループを抜ける
		if (c == '\n' || c == EOF)
		{
			break;
		}
	}

	// ファイルを閉じる
	fclose(fp);
	memset(buf, 0, sizeof(buf));

	// char配列作成
	char databuf[16] = "\0";

	// char配列に引数の数値を入れる
	sprintf_s(databuf, "%f,", data);

	// 文字列0とchar配列を連結
	strcat_s(charbuf[0], 128, databuf);

	// 文字列0と文字列1を連結
	strcat_s(charbuf[0], 128, charbuf[1]);

	// ファイルを開く
	result = fopen_s(&fp, name, "w");

	//エラーチェック
	if (result != 0)
	{
		printf("err : SaveData");
		return -1;
	}

	// ファイルに数値の書き込み
	fprintf(fp, "%s\n", charbuf[0]);

	// ファイルを閉じる
	fclose(fp);
	return 0;
}
