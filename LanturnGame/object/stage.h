#pragma once
#include "SphereCollider.h"

class Stage : public SphereCollider
{
private:

public:
    Stage();    //�R���X�g���N�^
    ~Stage();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc)const;   //�`�揈��

};