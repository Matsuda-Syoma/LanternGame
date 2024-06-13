#pragma once
#include "BoxCollider.h"

class Conveyor : public BoxCollider
{
private:
    int outimage;
    int inimage;
    float width, height;
    Vector2D location;
    int maxexpcnt = 80;
    int expcnt = maxexpcnt;
    int cnt = 0;
public:
    Conveyor();    //�R���X�g���N�^
    ~Conveyor();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc, float _distance)const;   //�`�揈��
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
