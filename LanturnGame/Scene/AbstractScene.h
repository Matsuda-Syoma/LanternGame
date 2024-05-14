#pragma once
#include "../Object/Notify.h"
#include "../Utility/common.h"

class AbstractScene {
protected:


public:
	Notify* notify;
	virtual ~AbstractScene() {};
	virtual AbstractScene* Update() = 0;
	virtual void Draw()const = 0;
};