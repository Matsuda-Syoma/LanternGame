#pragma once
#include "SphereCollider.h"

class Conveyor : public SphereCollider
{
private:

public:
    Conveyor();    //�R���X�g���N�^
    ~Conveyor();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc)const;   //�`�揈��

};
