#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"

Title::Title()
{
}

Title::~Title()
{
}

AbstractScene* Title::Update()
{
	return new GameMain;
	return this;
}

void Title::Draw() const
{
	DrawString(640, 360, "ここはタイトルです", 0xffffff);
}
