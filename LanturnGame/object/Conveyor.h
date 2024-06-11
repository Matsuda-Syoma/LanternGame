#pragma once
#include "BoxCollider.h"

class Conveyor : public BoxCollider
{
private:
    int images;
    float width, height;
    Vector2D location;
    int maxexpcnt = 80;
    int expcnt = maxexpcnt;
public:
    Conveyor();    //�R���X�g���N�^
    ~Conveyor();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc)const;   //�`�揈��
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
