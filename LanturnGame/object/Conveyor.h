#pragma once
#include "SphereCollider.h"

class Conveyor : public SphereCollider
{
private:

public:
    Conveyor();    //コンストラクタ
    ~Conveyor();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc)const;   //描画処理

};
