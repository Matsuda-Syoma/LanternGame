#pragma once
#include "CharaBase.h"

class Bomb : public CharaBase
{
private:
	static int images[];
	int mode = 0;				// �����^�C�v
	bool flg = true;			// �����Ă��邩
	bool expflg = false;		// ���΂��Ă��邩
	int maxexpcnt = 180;		// ���΂��甚������܂�
	int expcnt = maxexpcnt;		// ��������܂ł̎���
	int expsize = 10;			// �����̔����T�C�Y
	Vector2D velocity = 0;		// �ړ�Velocity
	Vector2D knockback = 0;		// �m�b�N�o�b�NVelocity
	Vector2D movetoloc = 0;		// �w����W

	//�p�[�e�B�N������x�����\��
	int HitCheck;

public:
	Bomb();
	~Bomb();
	void Initialize(GameMain* _g, int _obj_pos)override;
	void Finalize()override;
	void Hit(SphereCollider* _sphere)override;

	void Init(int _expsize);
	void Update(GameMain* _g)override;
	void Draw(CameraManager* camera)const override;
	bool GetFlg() const;
	void SetFlg(bool b);
	bool GetExpFlg() const;
	void SetExpFlg(bool b);

	void SetVelocity(Vector2D loc);
	void SetEXVelocity(Vector2D loc);

	void SetMode(int i);

	int GetMode();
	void SetKnockBack(Vector2D vec, int i);
	static void LoadImages();
	static void DeleteImages();
	Object* GetInsideBomb();

	//�p�[�e�B�N������x�����\��
	int hitcheck();
	void hitset();
};

