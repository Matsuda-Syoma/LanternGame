#include "Setting.h"
#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Setting::Setting()
{
	FILE* fp = nullptr;
	//ファイルオープン
	int result = fopen_s(&fp, "../Resources/setting.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		printfDx("err : setting");
	}

	//結果を読み込む
	fscanf_s(fp, "%f,\n", &deadzone);

	//ファイルクローズ
	fclose(fp);
}

Setting::~Setting()
{
}

AbstractScene* Setting::Update()
{
	return this;
}

void Setting::Draw() const
{
	DrawCircleAA(320.f, 320.f, 10.f, 24, 0xffff00, true);
	DrawCircleAA(320.f, 320.f, deadzone * 10.f, 24, 0xffff00, true);
	DrawString(640, 60, "ここは設定画面です", 0xffffff);
}
