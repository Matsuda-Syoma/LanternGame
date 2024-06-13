#include "LoadSounds.h"
#include "DxLib.h"
int Sounds::BGM_Game;
int Sounds::SE_Explosion[5];
int Sounds::BGM_GMain;
int Sounds::SE_Shoot;
int Sounds::SE_Hit;
int Sounds::SE_PlayerHit;
int Sounds::SE_CatchiPlayer;
int Sounds::SE_DeleteSoldier;
int Sounds::SE_MapClose;

int Sounds::BGM_Title;
int Sounds::SE_transition;
int Sounds::SE_cursor;

int Sounds::SE_CountDown;

void Sounds::LoadSounds() {
	BGM_Game = LoadSoundMem("Resources/sounds/BGM_Trip.wav");
	for (int i = 0; i < 5; i++)
	{
		SetCreateSoundPitchRate(500.0f * (i - 2));
		SE_Explosion[i] = LoadSoundMem("Resources/sounds/explosion_2.wav", 4);
	}
	SetCreateSoundPitchRate(0);

	BGM_GMain = LoadSoundMem("Resources/sounds/BGM_GMain.wav");
	SE_Shoot = LoadSoundMem("Resources/sounds/SE_Shoot.mp3");
	SE_Hit = LoadSoundMem("Resources/sounds/hit.wav");
	SE_PlayerHit = LoadSoundMem("Resources/sounds/SE_PlayerHit.mp3");
	SE_CatchiPlayer = LoadSoundMem("Resources/sounds/SE_CatchiPlayer.mp3");
	SE_DeleteSoldier = LoadSoundMem("Resources/sounds/SE_DeleteSoldier.mp3");
	SE_MapClose = LoadSoundMem("Resources/sounds/SE_MapClose.mp3");

	BGM_Title = LoadSoundMem("Resources/sounds/BGM_Title.wav");
	SE_transition = LoadSoundMem("Resources/sounds/SE_transition.mp3");
	SE_cursor = LoadSoundMem("Resources/sounds/SE_cursor.mp3");

	SE_CountDown = LoadSoundMem("Resources/sounds/SE_CountDwon.mp3");

	//SE_NextText = LoadSoundMem("Resources/sounds/SE_NextText.mp3");
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
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_Hit);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_PlayerHit);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_CatchiPlayer);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_DeleteSoldier);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_MapClose);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_transition);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_cursor);
		SetVolumeSoundMem((int)(_Volume * 39.216), Sounds::SE_CountDown);
		break;
	default:
		break;
	}
}
