#pragma once
class Description
{
public:
	Description();
	~Description();
	void Update();
	void Draw();

	int cheakTextNumber();
	//

private:
	//�摜�ǂݍ��ݗp�ϐ�
	//���e
	int ignited;
	int touchbomb;
	int bakuhatu;
	int chain;
	//����
	int touchsoldier;
	int be_pursued;

	int sankaku;

	//�摜�ړ��p�ϐ�
	int Movepng;
	int MovepngMax;
	bool page;

	//�\������text�m�F
	int textNumber;
};

