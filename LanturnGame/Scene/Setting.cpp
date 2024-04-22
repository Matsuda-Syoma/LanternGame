#include "Setting.h"
#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Setting::Setting()
{
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	int result = fopen_s(&fp, "../Resources/setting.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		printfDx("err : setting");
	}

	//���ʂ�ǂݍ���
	fscanf_s(fp, "%f,\n", &deadzone);

	//�t�@�C���N���[�Y
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
	DrawString(640, 60, "�����͐ݒ��ʂł�", 0xffffff);
}
