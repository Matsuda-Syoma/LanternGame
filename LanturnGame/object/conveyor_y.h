#pragma once
#include "BoxCollider.h"

class Conveyor_y : public BoxCollider
{
private:
    int images;
    float width, height;
    Vector2D location;
    int maxexpcnt = 80;
    int expcnt = maxexpcnt;
public:
    Conveyor_y();    //コンストラクタ
    ~Conveyor_y();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc, float _distance)const;   //描画処理
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
