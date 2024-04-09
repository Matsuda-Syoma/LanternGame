#include "PAD_INPUT.h"
#include "DxLib.h"

// デバッグモード
// #define __DEBUG__

int PAD_INPUT::NowKey[BUTTONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PAD_INPUT::OldKey[BUTTONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PAD_INPUT::KeyFlg[BUTTONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
XINPUT_STATE PAD_INPUT::Input;

void PAD_INPUT::UpdateInput() {
	// 現在の入力の取得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
	// 入力情報の反映
	for (int i = 0; i < BUTTONS; i++)
	{
		OldKey[i] = NowKey[i];
		NowKey[i] = Input.Buttons[i];
		KeyFlg[i] = NowKey[i] & ~OldKey[i];
	}

	// __DEBUG__マクロが定義されていたら
#ifdef __DEBUG__
	DebugInput();
#endif

}

void PAD_INPUT::DebugInput() {
	// 画面のクリア
	clsDx();

	printfDx("ボタンの入力情報\n");
	// 各ボタンの入力情報の出力
	for (int i = 0; i < BUTTONS; i++) {
		printfDx("OldKey: %d\tNowKey: %d\tKeyFlg: %d\n", OldKey[i], NowKey[i], KeyFlg[i]);
	}

	// スティックの入力情報の出力
	printfDx("\nスティックの入力情報\n");
	printfDx("LX: %d\tLY: %d\n", GetPadThumbLX(), GetPadThumbLY());
	printfDx("RX: %d\tRY: %d\n", GetPadThumbRX(), GetPadThumbRY());

	// トリガーの入力情報の出力
	printfDx("\nトリガーの入力情報\n");
	printfDx("LT: %d\n", GetLeftTrigger());
	printfDx("RT: %d\n", GetRightTrigger());
}