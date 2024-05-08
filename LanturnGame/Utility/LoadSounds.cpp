#include "LoadSounds.h"
#include "DxLib.h"
int Sounds::BGM_Game;
int Sounds::SE_Explosion;
int Sounds::SE_Shoot;
int Sounds::SE_Hit;
int Sounds::SE_PlayerHit;
int Sounds::SE_CatchiPlayer;
int Sounds::SE_DeleteSoldier;
int Sounds::SE_MapClose;

void Sounds::LoadSounds() {
	BGM_Game = LoadSoundMem("Resources/sounds/BGM_Trip.wav");
	SE_Explosion = LoadSoundMem("Resources/sounds/explosion_2.wav");
	SE_Shoot = LoadSoundMem("Resources/sounds/SE_Shoot.mp3");
	SE_Hit = LoadSoundMem("Resources/sounds/hit.wav");
	SE_PlayerHit = LoadSoundMem("Resources/sounds/SE_PlayerHit.mp3");
	SE_CatchiPlayer = LoadSoundMem("Resources/sounds/SE_CatchiPlayer.mp3");
	SE_DeleteSoldier = LoadSoundMem("Resources/sounds/SE_DeleteSoldier.mp3");
	SE_MapClose = LoadSoundMem("Resources/sounds/SE_MapClose.mp3");

}

void Sounds::AllStop() {

}