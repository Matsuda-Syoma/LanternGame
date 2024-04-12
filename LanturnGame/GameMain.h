#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
#include "Bomb.h"
#include "Explosion.h"
class GameMain : public AbstractScene
{
private:
	Bomb** bomb;
	Explosion** explosion;
public:
	GameMain();
	// �R���X�g���N�^
	~GameMain();								// �f�X�g���N�^

	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ����
	void Game();								// �Q�[���̏���
};

