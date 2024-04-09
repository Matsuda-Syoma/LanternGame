#pragma once

#include "DxLib.h"

#define BUTTONS 16

class PAD_INPUT {
private:
	static int NowKey[BUTTONS];
	static int OldKey[BUTTONS];
	static int KeyFlg[BUTTONS];

	// 現在の入力
	static XINPUT_STATE Input;

public:
	// パッド入力の更新
	static void UpdateInput();

	// 入力確認（デバッグ）
	static void DebugInput(); //デバッグ

	// 左スティック横
	static int GetPadThumbLX() { return Input.ThumbLX; }

	// 左スティック縦
	static int GetPadThumbLY() { return -Input.ThumbLY; }

	// 右スティック横
	static int GetPadThumbRX() { return Input.ThumbRX; }

	// 右スティック縦
	static int GetPadThumbRY() { return -Input.ThumbRY; }

	// LT押し具合
	static int GetLeftTrigger() { return Input.LeftTrigger; }

	// RT押し具合
	static int GetRightTrigger() { return Input.RightTrigger; }

	// ボタンを押され続けてる間１を返す
	static int GetNowKey(int key) { return NowKey[key]; }

	// ボタンを押した瞬間１を返す
	static int GetKeyFlg(int key) { return KeyFlg[key]; }
};

