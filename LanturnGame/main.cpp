#include"DxLib.h"
#include"Utility/common.h"
#include"Utility/FPSController.h"
#include"Scene/SceneManager.h"
#include"Scene/GameMain.h"
#include"Scene/Title.h"
#include"Scene/Setting.h"
#include"Utility/InputControl.h"
#include"Utility/LoadSounds.h"
#include"Utility/UserData.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// タイトルを設定
	SetMainWindowText("Lantern");

	SetWindowIconID(333);

	// ウィンドウモードで起動
	ChangeWindowMode(true);

	// ウィンドウサイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;

	// 描画先画面を裏にする（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);


	Sounds::LoadSounds();
	Sounds::SetSoundVolume(Sounds::BGM, UserData::LoadData(UserData::SOUNDS, 0));
	Sounds::SetSoundVolume(Sounds::SE, UserData::LoadData(UserData::SOUNDS, 1));

	SceneManager scene = (dynamic_cast<AbstractScene*>(new Setting()));

	FpsController FPSct(FRAMERATE, UPDATETIME);

	// ゲームループ
	while (ProcessMessage() == 0 && scene.Update() != nullptr) {


		InputControl::Update();
		// 画面の初期化
		ClearDrawScreen();
		// 描画処理
		scene.Draw();
		// 裏画面の内容を表に表示する
		FPSct.All();

		// 裏画面の内容を表に表示する
		ScreenFlip();
	}

	// DXライブラリの終了処理
	DxLib_End();

	return 0;
}
