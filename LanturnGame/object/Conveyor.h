#pragma once
#include "BoxCollider.h"

class Conveyor : public BoxCollider
{
private:
    int images;
    int image_con;
    int image_belt;
    int image_line;
    int image_left;
    int flame;
    float width, height;
    Vector2D location;
    int maxexpcnt = 80;
    int expcnt = maxexpcnt;
    int scroll;
public:
    Conveyor();    //コンストラクタ
    ~Conveyor();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc, float _distance)const;   //描画処理
    void Draw_left(Vector2D loc, float _distance)const;
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
