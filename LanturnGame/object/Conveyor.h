#pragma once
#include "BoxCollider.h"

class Conveyor : public BoxCollider
{
private:
    int images;
    int image_con;
    int image_belt;
    int flg;
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
    Vector2D GetLocation() const;
    void SetLocation(Vector2D loc);
};
