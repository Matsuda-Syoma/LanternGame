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
    Stage();    //コンストラクタ
    ~Stage();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc)const;   //描画処理
    /*float direction(Vector2D L);
    void SetVelocity(Vector2D loc);*/
};