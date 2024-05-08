#pragma once
class Sounds
{
public:
	static int BGM_Game;
	static int SE_Explosion;
	static int SE_Shoot;
	static int SE_Hit;
	static int SE_PlayerHit;
	static int SE_CatchiPlayer;
	static int SE_DeleteSoldier;
	static int SE_MapClose;

	static void LoadSounds();
	static void AllStop();
};

