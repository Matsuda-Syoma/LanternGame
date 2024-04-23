#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	bool hitflg = false;
	int cun = 0;			// ���G���ԃJ�E���g�p
	int animcun = 0;		// �A�j���[�V�����J�E���g�p
	int imgnum = 1;			// �摜�`��p�ϐ�
	int playerimg[12];		// �v���C���[�摜
	int direction = 4;		// �����擾
	int stopdirection = 0;

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
	void Invincible();

	// �A�j���[�V����
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	bool GetFlg() const;
	void SetFlg(bool b);
	Vector2D GetVelocity();
};

