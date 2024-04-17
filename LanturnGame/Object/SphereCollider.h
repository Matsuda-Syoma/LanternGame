#pragma once
#include "../Utility/Vector2D.h"

class SphereCollider 
{
protected:

	float radius; //���a
	Vector2D location;
public:
	SphereCollider(); //�R���X�g���N�^  (������)
	float GetRadius() const; //���a�̎擾
	bool HitSphere(SphereCollider* spherecollider)const; //�����蔻��
//	bool HitBox(class BoxCollider boxCollider) const;

	Vector2D GetLocation() const; //���S���W��擾
	void SetLocation(Vector2D loc); //���S���W��擾


};

