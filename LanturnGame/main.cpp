#include"DxLib.h"
#include"common.h"
#include"FPSController.h"
#include"SceneManager.h"
#include"GameMain.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	//タイトルを設定
	SetMainWindowText("Lantern");

	//ウィンドウモードで起動
	ChangeWindowMode(true);

	//ウィンドウサイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//DXライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;

	//描画先画面を裏にする（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager scene = (dynamic_cast<AbstractScene*>(new GameMain()));

	FpsController FPSct(FRAMERATE, UPDATETIME);

	//ゲームループ
	while (ProcessMessage() == 0 && scene.Update() != nullptr) {

		//画面の初期化
		PAD_INPUT::UpdateInput();			// PADの入力更新
		ClearDrawScreen();
		scene.Draw();
		//描画処理

		//裏画面の内容を表に表示する
		ScreenFlip();
	}

	//DXライブラリの終了処理
	DxLib_End();

	return 0;
}
