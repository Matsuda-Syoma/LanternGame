#pragma once
#include "BoxCollider.h"

class Conveyor : public BoxCollider
{
private:
    float width, height;
    Vector2D location;
public:
    Conveyor();    //コンストラクタ
    ~Conveyor();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc)const;   //描画処理
    void SetLocation(Vector2D loc);
};
