#include "Credit.h"
#include "DxLib.h"

Credit::Credit()
{
	//ComboEnd::LoadImages();

	creditimg = LoadGraph("Resources/images/brick.png");
	LoadDivGraph("Resources/images/alphabet.png", 26, 7, 4, 64, 64, alphabetimage);

}

Credit::~Credit()
{
}

AbstractScene* Credit::Update()
{
	time++;

	if (time >= 180) {
		return nullptr;
	}

	return this;
}

void Credit::Draw() const
{
	DrawGraph(0, 0, creditimg, true);

	char credit[] = "credit";
	for (int i = 0; i < sizeof(credit); i++)
	{
		int chr = credit[i] - 'a';
		DrawRotaGraph((SCREEN_WIDTH - 1100) + 56 * i, 150, 1.0, 0.0, alphabetimage[chr], true);
	}

	SetFontSize(40);
	DrawString((SCREEN_WIDTH - 1050), 250, "BGM\n�EDOVA-SYNDROME\n�E�Ȃ����肸�̉��y��\n", 0xffffff);
	DrawString((SCREEN_WIDTH - 1050), 400, "SE\n�E���ʉ����{\n�E������\n", 0xffffff);
	DrawString((SCREEN_WIDTH - 1050), 550, "�G�t�F�N�g\n�Efxmonster", 0xffffff);

	/*SetFontSize(40);
	DrawString((SCREEN_WIDTH - 1060), 400, "", 0xffffff);*/

}
