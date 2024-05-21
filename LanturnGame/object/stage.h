#pragma once
#include "SphereCollider.h"

class Stage : public SphereCollider
{
private:
    int radias;
    int images;
    int maxexpcnt = 180;
    int expcnt = maxexpcnt;
public:
    Stage();    //コンストラクタ
    ~Stage();   //デストラクタ

    void Update();      //描画以外の処理
    void Draw(Vector2D loc)const;   //描画処理
};