#include "PAD_INPUT.h"
#include "DxLib.h"

// �f�o�b�O���[�h
// #define __DEBUG__

int PAD_INPUT::NowKey[BUTTONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PAD_INPUT::OldKey[BUTTONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PAD_INPUT::KeyFlg[BUTTONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
XINPUT_STATE PAD_INPUT::Input;

void PAD_INPUT::UpdateInput() {
	// ���݂̓��͂̎擾
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
	// ���͏��̔��f
	for (int i = 0; i < BUTTONS; i++)
	{
		OldKey[i] = NowKey[i];
		NowKey[i] = Input.Buttons[i];
		KeyFlg[i] = NowKey[i] & ~OldKey[i];
	}

	// __DEBUG__�}�N������`����Ă�����
#ifdef __DEBUG__
	DebugInput();
#endif

}

void PAD_INPUT::DebugInput() {
	// ��ʂ̃N���A
	clsDx();

	printfDx("�{�^���̓��͏��\n");
	// �e�{�^���̓��͏��̏o��
	for (int i = 0; i < BUTTONS; i++) {
		printfDx("OldKey: %d\tNowKey: %d\tKeyFlg: %d\n", OldKey[i], NowKey[i], KeyFlg[i]);
	}

	// �X�e�B�b�N�̓��͏��̏o��
	printfDx("\n�X�e�B�b�N�̓��͏��\n");
	printfDx("LX: %d\tLY: %d\n", GetPadThumbLX(), GetPadThumbLY());
	printfDx("RX: %d\tRY: %d\n", GetPadThumbRX(), GetPadThumbRY());

	// �g���K�[�̓��͏��̏o��
	printfDx("\n�g���K�[�̓��͏��\n");
	printfDx("LT: %d\n", GetLeftTrigger());
	printfDx("RT: %d\n", GetRightTrigger());
}