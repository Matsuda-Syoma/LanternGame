﻿#include "SphereCollider.h"
#include<math.h>
#include "BoxCollider.h"


SphereCollider::SphereCollider()
{
	radius = 32;
}

bool SphereCollider::HitSphere(SphereCollider* spherecollider)const
{
	bool ret = false;	// 返り値
	float distance;		// 中心座標の距離

	// 中心座標の距離の計算
	distance = sqrtf(powf(spherecollider->GetLocation().x - location.x, 2) + powf(spherecollider->GetLocation().y - location.y, 2));

	if (distance < radius + spherecollider->GetRadius())  // 当たり判定
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitSphere(SphereCollider* spherecollider, float _radius) const
{
	bool ret = false;	// 返り値
	float distance;		// 中心座標の距離

	// 中心座標の距離の計算
	distance = sqrtf(powf(spherecollider->GetLocation().x - location.x, 2) + powf(spherecollider->GetLocation().y - location.y, 2));

	if (distance < _radius + spherecollider->GetRadius())  // 当たり判定
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitBox(BoxCollider boxCollider) const {
	Box box;
	boxCollider.GetSize(box.top, box.bottom, box.left, box.right);
	float width = box.right - box.left;
	float height = box.bottom - box.top;
	float centerX = box.right - width / 2.f;
	float centerY = box.bottom - height / 2.f;

	float distance = sqrtf(powf(location.x - centerX, 2) + powf(location.y - centerY, 2));
	float distanceX = sqrtf(powf(location.x - centerX, 2));
	float distanceY = sqrtf(powf(location.y - centerY, 2));

	if (distanceX < width / 2 + radius && distanceY < height / 2 + radius) {
		return true;
	}

	return false;
}

float SphereCollider::GetRadius()const
{
	return radius;
}

Vector2D SphereCollider::GetLocation() const
{
	return location;
}

void SphereCollider::SetLocation(Vector2D loc)
{
	this->location = loc;
}

