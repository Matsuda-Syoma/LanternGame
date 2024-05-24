#include "BoxCollider.h"
#include <math.h>
#include "DxLib.h"

BoxCollider::BoxCollider() {
	box.left = 0.0f;
	box.top = 0.0f;
	box.right = 0.0f;
	box.bottom = 0.0f;
}

void BoxCollider::GetSize(float& _top, float& _bottom, float& _left, float& _right) {
	_top = box.top;
	_bottom = box.bottom;
	_left = box.left;
	_right = box.right;
}

bool BoxCollider::HitBox(BoxCollider boxCollider) const {
	Box other;
	boxCollider.GetSize(other.top, other.bottom, other.left, other.right);
	if (box.bottom < other.top) {
		return false;
	}
	if (other.bottom < box.top) {
		return false;
	}
	if (box.right < other.left) {
		return false;
	}
	if (other.right < box.left) {
		return false;
	}

	return true;
}

bool BoxCollider::HitSphere(SphereCollider sphereCollider) const {
	float width = box.right - box.left;
	float height = box.bottom - box.top;
	float centerX = box.right - width / 2.f;
	float centerY = box.bottom - height / 2.f;

	float distance = sqrtf(powf(sphereCollider.GetLocation().x - centerX, 2) + powf(sphereCollider.GetLocation().y - centerY, 2));
	float distanceX = sqrtf(powf(sphereCollider.GetLocation().x - centerX, 2));
	float distanceY = sqrtf(powf(sphereCollider.GetLocation().y - centerY, 2));

	if (distanceX < width / 2 + sphereCollider.GetRadius() && distanceY < height / 2 + sphereCollider.GetRadius()) {
		return true;
	}

	return false;
}

void BoxCollider::DrawCollider() const {
	DrawBox(box.left, box.top, box.right, box.bottom, 0xFF, TRUE);
}