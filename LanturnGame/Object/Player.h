#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	Vector2D exvelocity;
	Vector2D lastinput = 0;
	bool pflg = true;			// �v���C���[�����t���O
	bool hitflg = false;		// �q�b�g�t���O
	bool hitsoldier = false;	// �q�b�g�t���O�i�����j
	bool overice = false;		// �X�̏��ɏ�����Ƃ��p�̃t���O
	bool onconveyor = false;	// �R���x�A�ɏ�����Ƃ��p�̃t���O
	bool blinkingflg = false;	// �_�Ńt���O
	int Invincible_cnt = 0;		// ���G���ԃJ�E���g�p
	int blinking_cnt = 0;		// �_�ŃJ�E���g�p
	int anim_cnt = 0;			// �A�j���[�V�����J�E���g�p
	int stan_cnt = 0;			// �X�^�����ԃJ�E���g�p
	int imgnum = 1;				// �摜�`��p�ϐ�
	int playerimg[12] = {};		// �v���C���[�摜
	int deadplayer_img = 0;		// �v���C���[�摜�i���S���j
	int angry_img = 0;			// �����ɕ߂܂������̉摜
	int direction = 4;			// ���݂̌����i�O�F���@�P�F���@�Q�F�E�@�R�F��j
	int stopdirection = 4;		// ���s���̌����i�S�F���@�T�F���@�U�F�E�@�V�F��j
	float deadzone = 0.1f;
	float acceleration = 1.f;
	float friction = .8f;
	float movelength = 0.0f;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(Vector2D loc, float _distance)const;
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
	bool GetHitSoldier() const;
	void SetHitSoldier(bool b);
	Vector2D GetVelocity();
	void SetVelocity(Vector2D loc);
	void SetLastInput();
	float GetNormalSpeed();
	int GetDirection();
};

