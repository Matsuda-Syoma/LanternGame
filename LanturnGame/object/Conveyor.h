#pragma once
#include "BoxCollider.h"

class Conveyor : public BoxCollider
{
private:
    int images;
    float width = 600.0f;
    float height = 100.0f;
    Vector2D location;
    int image_con;
    int image_belt;
    int image_line;
    int image_left;
    int flame;
    int maxexpcnt = 80;
    int expcnt = maxexpcnt;
    int scroll;
public:
    Conveyor();    //�R���X�g���N�^
    ~Conveyor();   //�f�X�g���N�^

    void Update();      //�`��ȊO�̏���
    void Draw(Vector2D loc, float _distance)const;   //�`�揈��
    void Draw_left(Vector2D loc, float _distance)const;
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
    float GetScale(int i);
};
