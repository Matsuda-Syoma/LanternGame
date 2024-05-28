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

int Sounds::SE_CntDown;

void Sounds::LoadSounds() {
	BGM_Game = LoadSoundMem("Resources/sounds/BGM_Trip.wav");
	for (int i = 0; i < 5; i++)
	{
		SetCreateSoundPitchRate(500.0f * (i - 2));
		SE_Explosion[i] = LoadSoundMem("Resources/sounds/explosion_2.wav");
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

	SE_CntDown = LoadSoundMem("Resources/sounds/SE_CountDwon.mp3");

	SE_NextText = LoadSoundMem("Resources/sounds/SE_NextText.mp3");
}

void Sounds::AllStop() {

}