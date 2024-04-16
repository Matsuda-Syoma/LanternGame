#pragma once
#include "../CharaBase.h"

class soldier : public CharaBase
{
public:
	soldier();
	~soldier();
	//初期化
	void Initialize();
	//更新
	void Upadate();
	void Draw();
};

