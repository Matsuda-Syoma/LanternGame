#pragma once
class Sounds
{
public:
	static int BGM_Game;
	static int SE_Explosion[5];
	static int SE_Shoot;
	static int SE_Hit;
	static int SE_PlayerHit;
	static int SE_CatchiPlayer;
	static int SE_DeleteSoldier;
	static int SE_MapClose;

	static int BGM_Title;
	static int SE_transition;
	static int SE_cursor;

	static void LoadSounds();
	static void AllStop();
};

