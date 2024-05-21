#include"DxLib.h"
#include"Utility/common.h"
#include"Utility/FPSController.h"
#include"Scene/SceneManager.h"
#include"Scene/GameMain.h"
#include"Scene/Title.h"
#include"Scene/Setting.h"
#include"Utility/InputControl.h"
#include"Utility/LoadSounds.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	//�^�C�g����ݒ�
	SetMainWindowText("Lantern");

	SetWindowIconID(333);

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(true);

	//�E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//DX���C�u�����̏���������
	if (DxLib_Init() == -1)return -1;

	//�`����ʂ𗠂ɂ���i�_�u���o�b�t�@�����O�j
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager scene = (dynamic_cast<AbstractScene*>(new GameMain()));

	FpsController FPSct(FRAMERATE, UPDATETIME);

	Sounds::LoadSounds();

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && scene.Update() != nullptr) {

		//��ʂ̏�����
		InputControl::Update();
		ClearDrawScreen();
		scene.Draw();
		FPSct.All();

		//����ʂ̓�e��\�ɕ\������
		ScreenFlip();
	}

	//DX���C�u�����̏I������
	DxLib_End();

	return 0;
}
