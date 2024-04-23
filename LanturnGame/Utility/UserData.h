#pragma once
class UserData
{
public:
	UserData(){}
	~UserData(){}
	static float LoadData(int i);
	static int SaveData(int i, float data);
};

