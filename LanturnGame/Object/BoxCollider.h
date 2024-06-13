#pragma once

#include "SphereCollider.h"

typedef struct Box {
	float top = 0.0f;
	float bottom = 0.0f;
	float left = 0.0f;
	float right = 0.0f;
} Box;

class BoxCollider
{
protected:
	
	Box box; //“–‚½‚è”»’è
public:
	BoxCollider();
	void GetSize(float& top, float& bottom, float& left, float& right);
	bool HitBox(BoxCollider boxCollider) const;
	bool HitSphere(SphereCollider sphereCollider) const;
	void DrawCollider() const;
	float GetSize(int i);
};

