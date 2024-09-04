#pragma once
#include "Object.h"

class GameMain;
class CameraManager;

class Stage : public Object
{
private:
    int images;

public:
    Stage();    //コンストラクタ
    ~Stage();   //デストラクタ

    void Initialize(GameMain* _g, int _obj_pos) override;
    void Finalize() override {};
    void Update(GameMain* _g) override;
    void Draw(CameraManager* camera)const override;
    void Hit(Object* _obj) override {};                         // 当たった時の処理
};