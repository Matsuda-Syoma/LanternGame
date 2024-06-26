#include "LoadSounds.h"
#include "DxLib.h"

int Sounds::BGM_Game;
int Sounds::SE_Explosion[5];
int Sounds::BGM_GMain;
int Sounds::SE_ComboEnd;
int Sounds::SE_Shoot;
int Sounds::SE_Hit;
int Sounds::SE_PlayerHit;
int Sounds::SE_CatchiPlayer;

int Sounds::SE_CD_Soldier;
int Sounds::SE_ED_Soldier;

int Sounds::SE_MapClose;

int Sounds::BGM_Title;
int Sounds::SE_transition;
int Sounds::SE_cursor;

int Sounds::SE_CountDown;

void Sounds::LoadSounds() {
	//BGM_Game = LoadSoundMem("Resources/sounds/BGM_Trip.wav");
	for (int i = 0; i < 5; i++)
	{
		SetCreateSoundPitchRate(500.0f * (i - 2));
		SE_Explosion[i] = LoadSoundMem("Resources/sounds/explosion_2.wav", 4);
	}
	SetCreateSoundPitchRate(0);

	BGM_GMain = LoadSoundMem("Resources/sounds/BGM_GMain.wav", 1);

	SE_Hit = LoadSoundMem("Resources/sounds/hit.wav");
	SE_ComboEnd = LoadSoundMem("Resources/sounds/explosion.wav");


	SE_CD_Soldier = LoadSoundMem("Resources/sounds/SE_sample/maou_se_8bit10.mp3",1);
	SE_ED_Soldier = LoadSoundMem("Resources/sounds/SE_sample/maou_se_battle_explosion06.mp3",1);


	SE_MapClose = LoadSoundMem("Resources/sounds/SE_MapClose.mp3");

	BGM_Title = LoadSoundMem("Resources/sounds/BGM_Title.wav", 1);
	SE_transition = LoadSoundMem("Resources/sounds/SE_transition.mp3");
	SE_cursor = LoadSoundMem("Resources/sounds/SE_cursor.mp3");
}

void Sounds::AllStop() {

}

void Sounds::SetSoundVolume(int _Type, int _Volume)
{
	switch (_Type)
	{
	case 0:
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::BGM_GMain);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::BGM_Title);
		break;
	case 1:
		for (int i = 0; i < 5; i++)
		{
			SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_Explosion[i]);
		}
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_Shoot);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_ComboEnd);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_Hit);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_PlayerHit);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_CD_Soldier);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_ED_Soldier);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_MapClose);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_transition);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_cursor);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_CountDown);
		break;
	default:
		break;
	}
}
