#pragma once
#include "../Utility/Vector2D.h"
class SphereCollider 
{
protected:

	float radius;
	Vector2D location;
public:
	SphereCollider();
	float GetRadius() const;
	bool HitSphere(SphereCollider* spherecollider)const;
	bool HitSphere(SphereCollider* spherecollider, float _radius)const;
	bool HitBox(class BoxCollider boxCollider) const;

	Vector2D GetLocation() const;
	void SetLocation(Vector2D loc);


};

