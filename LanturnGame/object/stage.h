#pragma once
#include "SphereCollider.h"

class Stage : public SphereCollider
{
private:
    int radias;
    int images;
    int maxexpcnt = 180;
    int expcnt = maxexpcnt;
   /* Vector2D velocity = 0;*/
public:
    Stage();    //�R���X�g���N�^
    ~Stage();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc)const;   //�`�揈��
    /*float direction(Vector2D L);
    void SetVelocity(Vector2D loc);*/
};