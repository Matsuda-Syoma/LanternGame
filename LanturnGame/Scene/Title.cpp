#include "Title.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "GameMain.h"
#include "Setting.h"


Title::Title()
{
}

Title::~Title()
{
}

AbstractScene* Title::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		// ��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	// �J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		// ��ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}



	// �J�[�\������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		switch (menu_cursor)
		{
		case 0:
			return new GameMain;
			break;
		case 1:
			return new Setting;
			break;
		case 2:
			//return new Help;
			break;
		default:
			//return new End;
			break;
		}
	}
	return this;
}

void Title::Draw() const
{
	DrawString(580, 60, "�����̓^�C�g���ł�", 0xffffff);
	DrawCircle(560, 340 + menu_cursor * 32, 8,0xffffff, TRUE);
	DrawString(580, 336 + (0 * 32), "�Q�[���X�^�[�g", 0xffffff);
	DrawString(580, 336 + (1 * 32), "�ݒ���", 0xffffff);
	DrawString(580, 336 + (2 * 32), "�w���v", 0xffffff);
	DrawString(580, 336 + (3 * 32), "�I��", 0xffffff);
}
