#pragma once
#include "CharaBase.h"

class Player : public CharaBase
{
private:
	Vector2D velocity;
	Vector2D exvelocity;
	Vector2D lastinput = 0;
	Vector2D knockback = 0;
	Vector2D vvec = 0;
	Vector2D length = 0;
	bool pflg = true;			// �v���C���[�����t���O
	bool hitflg = false;		// �q�b�g�t���O�i����or�����j
	bool hitsoldier = false;	// �q�b�g�t���O�i�����j
	bool ignitionflg = true;	// �_�΃t���O
	bool overice = false;		// �X�̏��ɏ�����Ƃ��p�̃t���O
	bool onconveyor = false;	// �R���x�A�ɏ�����Ƃ��p�̃t���O
	bool blinkingflg = false;	// �_�Ńt���O
	bool damagedirection = false;	// �_���[�W���o�p�̃t���O
	bool stickflg = false;			// �X�e�B�b�N���̓t���O
	bool crossbuttonflg = false;	// �\���{�^�����̓t���O

	int Invincible_cnt = 0;		// ���G���ԃJ�E���g�p
	int blinking_cnt = 0;		// �_�ŃJ�E���g�p
	int anim_cnt = 0;			// �A�j���[�V�����J�E���g�p
	int stan_cnt = 0;			// �X�^�����ԃJ�E���g�p
	int imgnum = 1;				// �摜�`��p�ϐ�
	int playerimg[12] = {};		// �v���C���[�摜
	int deadplayer_img = 0;		// �v���C���[�摜�i���S���j
	int angry_img = 0;			// �����ɕ߂܂������̉摜
	int direction = 4;			// ���݂̌����i�O�F���@�P�F���@�Q�F�E�@�R�F��j
	int stop_direction = 4;		// �~�܂����Ƃ��̌����i�S�F���@�T�F���@�U�F�E�@�V�F��j

	float deadzone = 0.1f;
	float acceleration = 1.f;
	float friction = .8f;
	float movelength = 0.0f;
	int areahitradius = 32;
	bool InputB = false;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(Vector2D loc, float _distance)const;
	void Movement();
	void Invincible();	// ���G����
	void Blinking();	// �_��
	void KnockBack(Vector2D EX);	// �m�b�N�o�b�N

	// �A�j���[�V����
	void MoveRight();	// �E�ړ�
	void MoveLeft();	// ���ړ�
	void MoveUp();		// ��ړ�
	void MoveDown();	// ���ړ�

	bool GetHitFlg() const;
	void SetHitFlg(bool b);
	bool GetPlayerFlg() const;
	void SetPlayerFlg(bool b);
	bool GetIgnitionFlg() const;
	void SetIgnitionFlg(bool b);
	bool GetIceFlg() const;
	void SetIceFlg(bool b);
	bool GetConFlg() const;
	void SetConFlg(bool b);
	bool GetHitSoldier() const;
	void SetHitSoldier(bool b);
	bool GetIDamageDirectionFlg() const;
	void SetDamageDirectionFlg(bool b);

	Vector2D GetVelocity();
	void SetVelocity(Vector2D loc);
	void SetLastInput();
	float GetNormalSpeed();
	float GetLength(Vector2D loc);
	int GetDirection();
	void SetKnockBack(Vector2D vec, int i);

};

