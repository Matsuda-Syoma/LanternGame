#pragma once
#include "../Utility/common.h"

class AbstractScene {
protected:


public:
	virtual ~AbstractScene() {};
	virtual AbstractScene* Update() = 0;
	virtual void Draw()const = 0;
};