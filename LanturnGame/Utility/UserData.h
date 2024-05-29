#pragma once
class UserData
{
private:
	static char buf[1024];
	static char c;
public:
	enum Type
	{
		SETTING = 0,
		HISCORE,
		SOUNDS
	};
	UserData(){}
	~UserData(){}
	static float LoadData(int filenum, int num);
	static float LoadData(int filenum);
	static float SaveData(int filenum, int num, float data);
};

