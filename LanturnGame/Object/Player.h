#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	bool hitflg = false;
	bool blinkingflg = false;	// �_�Ńt���O
	int cun = 0;				// ���G���ԃJ�E���g�p
	int blinkingcun = 0;		// �_�ŃJ�E���g�p
	int animcun = 0;			// �A�j���[�V�����J�E���g�p
	int imgnum = 1;				// �摜�`��p�ϐ�
	int playerimg[12];			// �v���C���[�摜
	int direction = 4;			// ���s���̌����i�O�F���@�P�F���@�Q�F�E�@�R�F��j
	int stopdirection = 4;		// �����~�܂������̌����i�S�F���@�T�F���@�U�F�E�@�V�F��j
	float deadzone = 0.1;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
	void Invincible();	// ���G����
	void Blinking();	// �_��

	// �A�j���[�V����
	void MoveRight();	// �E�ړ�
	void MoveLeft();	// ���ړ�
	void MoveUp();		// ��ړ�
	void MoveDown();	// ���ړ�

	bool GetFlg() const;
	void SetFlg(bool b);
	Vector2D GetVelocity();
};

