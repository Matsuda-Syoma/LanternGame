#pragma once
class UserData
{
public:
	UserData(){}
	~UserData(){}
	static float LoadData(int i);
	int SaveData(int i, float data);
};

