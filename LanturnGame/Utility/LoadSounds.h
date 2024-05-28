#pragma once
class Sounds
{
public:
	enum Type
	{
		BGM = 0,
		SE
	};
	static int BGM_Game;
	static int SE_Explosion[5];
	static int BGM_GMain;
	static int SE_Shoot;
	static int SE_Hit;
	static int SE_PlayerHit;
	static int SE_CatchiPlayer;
	static int SE_DeleteSoldier;
	static int SE_MapClose;

	static int BGM_Title;
	static int SE_transition;
	static int SE_cursor;
	static int SE_CntDown;
	//static int SE_NextText;

	static void LoadSounds();
	static void AllStop();
	static void SetSoundVolume(int _Type, int _Volume);
};

