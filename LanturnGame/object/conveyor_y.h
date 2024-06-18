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
    Conveyor_y();    //コンストラクタ
    ~Conveyor_y();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc, float _distance)const;   //描画処理
    void Draw_up(Vector2D loc, float _distance)const;   //描画処理
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
