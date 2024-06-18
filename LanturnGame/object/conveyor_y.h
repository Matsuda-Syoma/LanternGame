#pragma once
#include "BoxCollider.h"

class Conveyor_y : public BoxCollider
{
private:
    int images;
    int image_con;
    int image_belt;
    int image_line;
    int image_up;
    int scroll;
    float width, height;
    Vector2D location;
    int maxexpcnt = 80;
    int expcnt = maxexpcnt;
public:
    Conveyor_y();    //�R���X�g���N�^
    ~Conveyor_y();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc, float _distance)const;   //�`�揈��
    void Draw_up(Vector2D loc, float _distance)const;   //�`�揈��
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
