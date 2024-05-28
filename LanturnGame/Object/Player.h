#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	Vector2D exvelocity;
	Vector2D lastinput = 0;
	bool pflg = true;			// �����t���O
	bool hitflg = false;		// �q�b�g�t���O
	bool hit_soldier = false;
	bool overice = false;
	bool onconveyor = false;
	bool blinkingflg = false;	// �_�Ńt���O
	int cun = 0;				// ���G���ԃJ�E���g�p
	int blinkingcun = 0;		// �_�ŃJ�E���g�p
	int animcun = 0;			// �A�j���[�V�����J�E���g�p
	int imgnum = 1;				// �摜�`��p�ϐ�
	int playerimg[12] = {};		// �v���C���[�摜
	int d_playerimg = 0;		// �v���C���[�摜�i���S���j
	int angryimg = 0;
	int direction = 4;			// ���݂̌����i�O�F���@�P�F���@�Q�F�E�@�R�F��j
	int stopdirection = 4;		// ���s���̌����i�S�F���@�T�F���@�U�F�E�@�V�F��j
	int pointflg = 0;
	int countflg = 0;
	int stan = 0;
	float deadzone = 0.1f;
	float acceleration = 1.f;
	float friction = .8f;
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
	bool GetPFlg() const;
	void SetPFlg(bool b);
	bool GetIceFlg() const;
	void SetIceFlg(bool b);
	bool GetConFlg() const;
	void SetConFlg(bool b);
	void SetHitSoldier(bool b);
	Vector2D GetVelocity();
	void SetVelocity(Vector2D loc);
	void SetLastInput();
};

