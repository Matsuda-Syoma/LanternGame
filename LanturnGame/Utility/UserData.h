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
	static float LoadData(int i);
	static int SaveData(int i, float data);
	static float Test(int filenum, int num);
	static float Test2(int filenum, int num, float data);
};

